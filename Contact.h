#include<string>
using namespace std;
class Contact {
private:
    string _Fname;
    string _Lname;
    string _phone;
public:
    Contact() {
    } //default
    Contact(string Fname, string Lname, string phone); //3 pm
    void setContactFName(string Fname);
    void setContactLName(string Lname);
    void setContactPhone(string phone);
    string getContactFName();
    string getContactLName();
    string getContactPhone();
    bool operator==(const Contact& person1);
    bool operator!=(const Contact& person1);
    bool operator<(const Contact& person1);
    bool operator>(const Contact& person1);
    friend void print(Contact &);
    friend ostream &operator<<(ostream &os, Contact &person);
    virtual ~Contact();
};
Contact::Contact(string Fname, string Lname, string phone) {
    //assign passed values
    _Fname = Fname;
    _Lname = Lname;
    _phone = phone;
}
Contact::~Contact() {
}

void Contact::setContactFName(string Fname) {
    _Fname = Fname;
}

void Contact::setContactLName(string Lname) {
    _Lname = Lname;
}

void Contact::setContactPhone(string phone) {
    _phone = phone;
}

string Contact::getContactFName() {
    return _Fname;

}

string Contact::getContactLName() {
    return _Lname;

}

string Contact::getContactPhone() {
    return _phone;
}

void print(Contact& person) { //friend function
    cout << person.getContactFName() << " " << person.getContactLName() << " "
         << person.getContactPhone() << endl;
}

bool Contact::operator==(const Contact& p1) {

    return (p1._Fname == this->_Fname && p1._Lname == this->_Lname);

}

bool Contact::operator!=(const Contact& p1) {

    return (p1._Fname != this->_Fname && p1._Lname != this->_Lname);

}

bool Contact::operator<(const Contact& p1) {

    return (this->_Fname + this->_Lname < p1._Fname + p1._Lname);

}

bool Contact::operator>(const Contact& p1) {

    return (this->_Fname + this->_Lname > p1._Fname + p1._Lname);

}

ostream &operator<<(ostream &os, Contact &person) {

    os << person.getContactFName() << " " << person.getContactLName() << ":"
       << person.getContactPhone() << endl;

    return os;
}
