#ifndef TEST1_H
#define TEST1_H
#include <QTest>
#include <QDebug>
#include <PtrHelpers.h>
class TestSharedPtr: public QObject
{
    Q_OBJECT
private slots:
    void testLifeCycle();
    void testMakeShared();
    void testReset();
    void testDownCasting();
    void testAllocationForObject();
};

class DemoController: public Interface
{
public:
    virtual void* cast(InterfaceID id) override
    {
        if (id == iid<DemoController>)
        {
            return static_cast<void*>(this);
        }
        return nullptr;
    }
};


class DemoObject: public AppendCountableHelper<DemoObject, DemoController>
{
public:
    DemoObject(bool* destructorFlag = nullptr)
    {
        m_destructorFlag = destructorFlag;
    }
    virtual ~DemoObject()
    {
        if (m_destructorFlag)
        *m_destructorFlag = true;
    }

    virtual void* cast(InterfaceID id) override
    {
        if (id == iid<DemoObject>)
        {
            return static_cast<void*>(this);
        }
        return support_query(id);
    }
private:
    bool* m_destructorFlag = nullptr;
};

REGISTER_SYS_INTERFACE(DemoObject);
REGISTER_SYS_INTERFACE(DemoController);

void TestSharedPtr::testLifeCycle()
{
    bool isDestructorCalled = false;
    {
        SharedPtr<DemoObject> ptr1;
        DemoObject* demo = new DemoObject(&isDestructorCalled);
        {
            QCOMPARE(demo->refCount(), 0);
            SharedPtr<DemoObject> ptr2(demo);
            QCOMPARE(demo->refCount(), 1);
            ptr1 = ptr2;
            QCOMPARE(demo->refCount(), 2);
        };
        QCOMPARE(isDestructorCalled, false);
        QCOMPARE(demo->refCount(), 1);
    }
    QCOMPARE(isDestructorCalled, true);
}

void TestSharedPtr::testMakeShared()
{
    bool isDestructorCalled = false;
    {
        SharedPtr<DemoObject> ptr1 = makeRef<DemoObject>(&isDestructorCalled);
        QVERIFY2(ptr1->refCount() == 1, "The reference Count must be 1");
    }
    QCOMPARE(isDestructorCalled, true);
}

void TestSharedPtr::testReset()
{
    bool isDestructorCalled = false;
    {
        SharedPtr<DemoObject> ptr1 = makeRef<DemoObject>(&isDestructorCalled);
        QVERIFY2(ptr1->refCount() == 1, "The reference Count must be 1");
        ptr1.reset();
        QCOMPARE(isDestructorCalled, true);
    }
    {
        isDestructorCalled = false;
        SharedPtr<DemoObject> ptr1 = makeRef<DemoObject>(&isDestructorCalled);
        SharedPtr<DemoObject> ptr2 = ptr1;
        QCOMPARE(ptr1->refCount(), 2);
        ptr1.reset();
        QCOMPARE(ptr1.get(), nullptr);
        QCOMPARE(ptr2->refCount(), 1);
    }
    QCOMPARE(isDestructorCalled, true);

}

void TestSharedPtr::testDownCasting()
{
    // Use the shared pointer of the Parent class to points to the Derived class
    bool isDestructorCalled = false;
    {
        SharedPtr<DemoObject> ptr1 = makeRef<DemoObject>(&isDestructorCalled);
        QCOMPARE(ptr1->refCount(),1);
        SharedPtr<DemoController> ptr2 = ptr1;
        QCOMPARE(ptr1->refCount(),2);
        ptr2.reset();
        QCOMPARE(ptr1->refCount(),1);
        DemoController* getDemoController = ptr1.get<DemoController>();
        QVERIFY2(getDemoController != nullptr, "Have to down cast succes");
    };
    QCOMPARE(isDestructorCalled, true);
}

void TestSharedPtr::testAllocationForObject()
{
    bool isWarningStackAllocation = false;
    try
    {
        DemoObject object;
    }
    catch(const std::runtime_error& err)
    {
        isWarningStackAllocation = true;
    }
    catch(...)
    {
        qCritical() << "Undefined exception";
    }
    QCOMPARE(isWarningStackAllocation, true);
}

QTEST_MAIN(TestSharedPtr)
#include "TestSharedPtr.moc"

#endif // TEST1_H
