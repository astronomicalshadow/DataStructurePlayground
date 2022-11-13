#include <iostream>

class Obj;

class StateMachine
{
public:
    virtual void Start() = 0;
    virtual void Update(Obj* Obj) = 0 ;
    virtual void End() = 0;
};

class Obj
{
public:
    Obj();

    void Update();
    void SwitchStates(StateMachine* SM);

    ~Obj(){};

private:
    StateMachine* pCurrent;
};


class StateA : public StateMachine
{
public:
    void Start();
    void Update(Obj* Obj);
    void End();
    static StateMachine& GetInstance()
    {
        // no pointers, no mem leak
        static StateA Singleton;
        return Singleton;
    };

private:
    StateA(){};
};

class StateB : public StateMachine
{
public:
    void Start();
    void Update(Obj* Obj);
    void End();
    static StateMachine& GetInstance()
    {
        // no pointers, no mem leak
        static StateB Singleton;
        return Singleton;
    };

private:
    StateB(){};
};

// Obj
Obj::Obj()
{
    pCurrent = &StateA::GetInstance();
};

void Obj::Update()
{
    pCurrent->Update(this);
};

void Obj::SwitchStates(StateMachine* SM)
{
    pCurrent->End();
    pCurrent = SM;
    pCurrent->Start();
}

// StateA
void StateA::Start()
{
    std::cout << "Starting A \n";
}
void StateA::Update(Obj* Obj)
{
    std::cout << "Updating A \n";
    Obj->SwitchStates(&StateB::GetInstance());
};
void StateA::End()
{
    std::cout << "Exiting A \n";
}

// StateB
void StateB::Start()
{
    std::cout << "Starting B \n";
}
void StateB::Update(Obj* Obj)
{
    std::cout << "Updating B \n";
    Obj->SwitchStates(&StateA::GetInstance());
};
void StateB::End()
{
    std::cout << "Ending B \n";
}


int main()
{
    Obj a;
    for(int i = 0; i < 4; i++)
    {
        a.Update();
    }

    std::cout << "ending...";
}
