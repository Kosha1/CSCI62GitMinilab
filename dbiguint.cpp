#include "dbiguint.h"


//default constructor
dbiguint::dbiguint(){
  capacity_ = 1;
  data_ = new unsigned short[capacity_];
  data_[0] = 0;
}

//regular constructor
dbiguint::dbiguint(const string& s){
  capacity_ = s.length();
  data_ = new unsigned short[capacity_];
  for (int i = 0; i < capacity_; i++){
    data_[i] = s.at(capacity_ - 1 - i) - '0';
  }
}

//destructor
dbiguint::~dbiguint(){
  capacity_ = 0;
  delete []data_;
}

int dbiguint::size()const{
  return capacity_;
}

unsigned short dbiguint::operator [](int pos)const{
  if (pos >= capacity_ || pos < 0) return 10;
  else return data_[pos];
}

std::ostream& operator << (std::ostream& out, const dbiguint& b){
  for(int i = b.size()-1; i >= 0; i--){
    out<<b[i];
  }
  return out;
}

void dbiguint::reserve(int newcapacity){
  if (newcapacity < capacity_ && newcapacity > 0){//reduction only possible if leading zeros present
    int increment = 0;
    while (capacity_ - increment > newcapacity){
      if (data_[capacity_ - increment - 1] != 0) return;
      else increment++;
    }
    unsigned short* temp = new unsigned short[newcapacity];
    for (int i = 0; i < newcapacity; i++){
      temp[i] = data_[i];
    }
    capacity_ = newcapacity;
    delete[] data_;
    data_ = temp;

  }
  else if (newcapacity == 0){//0 as an argument will remove any leading zeros
    int increment = 0;
    while (data_[capacity_ - increment - 1] == 0 && capacity_ - increment - 1 >=0){
      increment++;
    }
    capacity_ -= increment;
    unsigned short* temp = new unsigned short[capacity_];
    for (int i = 0; i < capacity_; i++){
      temp[i] = data_[i];
    }
    delete[] data_;
    data_ = temp;

  }
  else if (capacity_ == newcapacity) return;
  else{
    unsigned short* temp = new unsigned short[newcapacity];
    for (int i = 0; i < newcapacity; i++){
      if (i < capacity_) temp[i] = data_[i];
      else temp[i] = 0;
    }
    capacity_ = newcapacity;
    delete [] data_;
    data_ = temp;
  }
}

void dbiguint::operator +=(const dbiguint& b){
  int realBcap = b.capacity_;//this is the length of the int without leading zeros
  //reserve can mess things up if called earlier

  while (b[realBcap - 1] == 0){
    realBcap --;
  }
  if (realBcap > capacity_){
    reserve(realBcap);
  }

  int iterations = capacity_;

  for (int i = 0; i < iterations; i++){
    int bVal = 0;
    if (b[i] != 10) bVal = b[i];
    int sum = data_[i] + bVal;
    data_[i] = sum % 10;
    if (sum >=10){
      if (i<iterations-1){
        data_[i+1] ++;
      }
      else {
        reserve(capacity_+1);
        data_[i+1]++;
      }
    }
  }
}

dbiguint operator +(const dbiguint & a, const dbiguint & b){
  dbiguint c;
  c+=a;
  c+=b;
  return c;
}

int dbiguint::compare(const dbiguint & b) const{
  int realCap = capacity_;
  while (data_[realCap - 1] == 0 && realCap - 1 >= 0){
    realCap --;
  }

  int realBCap = b.capacity_;
  while (b[realBCap - 1] == 0){
    realBCap --;
  }

  if (realCap > realBCap) return 1;
  else if (realBCap > realCap) return -1;
  else{
    for (int i = realCap; i >= 0; i--){
      if (data_[i] > b.data_[i]) return 1;
      if (data_[i] < b.data_[i]) return -1;
    }
  }
  return 0;

}

bool operator < (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) == -1) return true;
  else return false;
}

bool operator <= (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) == -1 || a.compare(b) == 0) return true;
  else return false;
}

bool operator == (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) == 0) return true;
  else return false;
}

bool operator != (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) != 0) return true;
  else return false;
}

bool operator >= (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) == 1 || a.compare(b) == 0) return true;
  else return false;
}

bool operator > (const dbiguint & a, const dbiguint & b){
  if (a.compare(b) == 1) return true;
  else return false;
}

void dbiguint::operator =(const dbiguint & b){
  unsigned short* temp = new unsigned short [b.capacity_];
  capacity_ = b.capacity_;
  for (int i = 0; i < capacity_; i++){
    temp[i] = b[i];
  }
  delete [] data_;
  data_ = temp;
}

void dbiguint::operator -=(const dbiguint & b){
  if (b >= *this) {
    dbiguint temp;
    *this = temp;
  }
  else{
    for (int i = 0; i < b.capacity_; i++){
      int diff = data_[i] - b[i];
      if (diff < 0){
        data_[i] = diff+10;
        int count = 1;
        while (data_[i+count] == 0 && i < capacity_ - 1){
          data_[i+count] = 9;
          count++;
        }
        data_[i+count] --;
      }
      else data_[i] = diff;
    }
    reserve(0);
  }
}

void dbiguint::operator *=(const dbiguint & b){
  dbiguint temp;//this should equal 0
  if (*this == temp || b == temp){
    *this = temp;
  }
  else{
    int minCap;
    int maxCap;
    bool thisFirst;//true if this has >= capacity, false otherwise
    if (capacity_ >= b.capacity_){
      minCap = b.capacity_;
      maxCap = capacity_;
      thisFirst = true;
    }
    else{
      maxCap = b.capacity_;
      minCap = capacity_;
      thisFirst = false;
    }

    dbiguint answer;

    if (thisFirst){//this object is on top of b in multiplaction table
      for (int i = 0; i < minCap; i++){
        dbiguint temp;
        temp.reserve(maxCap + i);
        for (int j = 0; j < maxCap; j++){
          int product = data_[j] * b[i];
          int productSum = product + temp[i+j];
          temp.data_[i+j] = productSum % 10;
          if (productSum > 9){
            if (temp[i+j+1] > 9){
              temp.reserve(maxCap+1+i);
              temp.data_[i+j+1] += productSum/10;
            }
            else temp.data_[i+j+1] += productSum/10;
          }
        }
        answer+=temp;
      }
      *this = answer;
    }
    else{
      for (int i = 0; i < minCap; i++){
        dbiguint temp;
        temp.reserve(maxCap + i);
        for (int j = 0; j < maxCap; j++){
          int product = b[j] * data_[i];
          int productSum = product + temp[i+j];
          temp.data_[i+j] = productSum % 10;
          if (product > 9){
            if (temp[i+j+1] > 9){
              temp.reserve(maxCap+1+i);
              temp.data_[i+j+1] += productSum/10;
            }
            else temp.data_[i+j+1] += productSum/10;
          }
        }
        answer+=temp;
      }
      *this = answer;
    }
  }
}

void dbiguint::clean(){
  int realCap = capacity_;
  for (int i = capacity_ - 1; i >=0; i--){
    if (data_[i] == 0) realCap --;
    else break;
  }
  if (realCap == 0) realCap = 1;
  capacity_ = realCap;
  unsigned short* temp = new unsigned short [capacity_];
  for (int i = 0; i < capacity_; i++){
    temp[i] = data_[i];
  }
  delete data_;
  data_ = temp;
}
