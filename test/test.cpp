#include <iostream>
#include <PtrHelpers.h>
class DemoObject: 
    public AppendCountableHelper<DemoObject, Interface>
{
    public:
        DemoObject()
        {
            std::cout << "Create demo object " << this << "\n";
        }
        virtual ~DemoObject()
        {
            std::cout << "Call destruct\n";
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

int main(int argc, char** argv)
{
    {
        SharedPtr<DemoObject> refPtr1;
        {
            DemoObject *object = new DemoObject();
            SharedPtr<DemoObject> refPtr2(object);
            refPtr1 = refPtr2;
        }
        std::cout << "Get out the first scope\n";
    }
    std::cout << "Get out the second scope\n";

    // {
    //     auto sharedPtr = makeRef<DemoObject>();
    // }

}
