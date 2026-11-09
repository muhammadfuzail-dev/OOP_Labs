#include <iostream>
#include <string>
using namespace std;
class Marker{
    public:
    explicit Marker (const string& label):name{label}{
        cout<<"construct "<<name<<endl;
    }
    ~Marker(){
        cout<<"Destroy "<<name<<endl;
    }
    private:
    string name;
};
class Account{
    public:
    Account(const string& AccountName, int initialBalance){
        name=AccountName;
        if(initialBalance>=0){
            balance=initialBalance;
        }
        else {
            balance=0;
        }
    }
    void setName(const string& name){
        this->name=name;
    }
    void deposit(int amount){
        if(amount>0){
            balance+=amount;
        }
        cout<<"Account name = "<<name<<" balance ="<<balance<<endl;
    }
    string getName()const{
        return name;
    }
    int getBalance()const {
        return balance;
    }
    private:
    string name;
    int balance;

};
class OwnedScore{
    public:
    explicit OwnedScore (int initial):value{new int(initial)}{}
    ~OwnedScore(){
        delete value;
    }
    void setValue(int value){
        *(this->value)=value;
    }
    int getValue()const{
        return *value;
    }
    private:
     int* value;
};
class ParkingMeter{
    public:
    ParkingMeter(const string& zoneName , int maximumMinutes)
    : zoneName(zoneName.empty() ? "UNKNOWN" : zoneName),
      maximumMinutes(maximumMinutes > 0 ? maximumMinutes : 60),
      remainingMinutes(new int(0)){
    }
    ~ParkingMeter(){
        delete remainingMinutes;
    }
    bool addMinutes(int minutes){
        if(minutes>0    &&  (*remainingMinutes+minutes)<=maximumMinutes){
            *remainingMinutes=*remainingMinutes+minutes;
            return true;
        }
        return false;
    }
    bool useMinutes(int minutes){
        if(minutes>0    &&  minutes<=*remainingMinutes){
            *remainingMinutes-=minutes;
            return true;
        }
        return false;
    }
    string getZone() const{
        return zoneName;
    }
    int getRemaining()const {
        return *remainingMinutes;
        }
    private:
    string zoneName;
    int maximumMinutes;
    int* remainingMinutes;

};
void traceAutomaticObject(){
    cout<<"begin trace"<<endl;
    Marker first{"first"};
    {
        Marker second{"second"};
        cout<<"inside Block"<<endl;
    }
    cout<<"After block "<<endl;
}
void printAccount(const Account& account){
    cout<<"ACCOUNT name="<<account.getName()<<" balance="<<account.getBalance()<<endl;

}
bool depositIfPositive(Account& account,int amount){
    if(amount<0)return false;
    account.deposit(amount);
    return true;
}
void inspectAccount(const Account* account){
    if(account!=nullptr){
        printAccount(*account);
    }
    else{
        cout<<"ACCOUNT Absent\n";
    }
}
void useDynamicScore(){
    OwnedScore* score{new OwnedScore{20}};
    cout<<"SCORE Dynamic="<<score->getValue()<<endl;
    score->setValue(25);
    cout<<"SCORE Dynamic="<<score->getValue()<<endl;
    delete score;
    score=nullptr;
    cout<<"POINTER cleared="<<(score==nullptr?"true":"false")<<endl;



}
int main(){ 
    traceAutomaticObject();
    cout<<endl;
    Account account{"Areeba",50};
    account.setName("Areeba Khan");
    account.deposit(25);
    cout<<endl;
    Account account1{"Bilal",10};
    printAccount(account1);
    cout<<"Deposit Result="<<(depositIfPositive(account1,5)?"true":"false")<<endl;
    cout<<"Deposit Result="<<(depositIfPositive(account1,-2)?"true":"false")<<endl;
    inspectAccount(&account1);
    inspectAccount(nullptr);
    cout<<endl;
    OwnedScore automatic{10};
    automatic.setValue(15);
    cout<<"Score automatic="<<automatic.getValue()<<endl;
    cout<<endl;
    useDynamicScore();
    cout<<endl;
    ParkingMeter meter{"P-12",30};
    cout<<"D1 remaining="<<meter.getRemaining()<<endl;
    cout<<"D2 add(10)="<<(meter.addMinutes(10)?"true":"false")<<" remaining="<<meter.getRemaining()<<endl;
    cout<<"D3 add(25)="<<(meter.addMinutes(25)?"true":"false")<<" remaining="<<meter.getRemaining()<<endl;
    cout<<"D4 use(4)="<<(meter.useMinutes(4)?"true":"false")<<" remaining="<<meter.getRemaining()<<endl;
    cout<<"D5 use(10)="<<(meter.useMinutes(10)?"true":"false")<<" remaining="<<meter.getRemaining()<<endl;
    cout<<"D6 addNegative="<<(meter.addMinutes(-2)?"true":"false")<<" remaining="<<meter.getRemaining()<<endl;
    ParkingMeter invalid{"",-1};
    cout<<"D7 FallBack Zone="<<invalid.getZone()<<" remaining="<<invalid.getRemaining()<<endl;
    ParkingMeter* DynamicMeter{new ParkingMeter{"d-7",20}};
    DynamicMeter->addMinutes(20);
    cout<<"D8 dynamic remaining="<<DynamicMeter->getRemaining()<<endl;
    delete DynamicMeter;
    DynamicMeter=nullptr;
    cout<<"D9 pointer Cleared="<<(DynamicMeter==nullptr?"true":"false")<<endl;
    return 0;
}