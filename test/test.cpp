#include <iostream>
#include <PtrHelpers.h>

class DemoController: public Interface
{
public:
    DemoController()
    {
        // std::cout << "Construct Controller\n";
    }
    ~DemoController()
    {
        // std::cout << "Destruct Controller\n";
    }
    virtual void* cast(InterfaceID id) override
    {
        if (id == iid<DemoController>)
        {
            return static_cast<void*>(this);
        }
        std::cout <<__LINE__ << " Call casting herere\n";
        return nullptr;
    }
};


class DemoObject: 
    public AppendCountableHelper<DemoObject, DemoController>
{
    public:
        DemoObject()
        {
            // std::cout << "Create demo object " << this << "\n";
        }
        virtual ~DemoObject()
        {
            // std::cout << "Call destruct\n";
        }

        virtual void* cast(InterfaceID id) override
        {
            if (id == iid<DemoObject>)
            {
                return static_cast<void*>(this);
            }
            return support_query(id);
        }
};

REGISTER_SYS_INTERFACE(DemoObject);
REGISTER_SYS_INTERFACE(DemoController);

int main(int argc, char** argv)
{
    {
        SharedPtr<DemoObject> refPtr1 = makeRef<DemoObject>();
        refPtr1->cast(iid<DemoController>);
        DemoController* controller = refPtr1.get<DemoController>();
        std::cout << "The address is " <<controller << "\n";
    }

}
