#ifndef TEST2_H
#define TEST2_H
#include <QTest>
#include <PtrHelpers.h>
class TestWeakPtr: public QObject
{
    Q_OBJECT
private slots:
    void testLifeCycle();
};

class DemoObject: public AppendCountableHelper<DemoObject>
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

void TestWeakPtr::testLifeCycle()
{
    bool isDestructorCalled = false;
    {
        SharedPtr<DemoObject> obj = makeRef<DemoObject>(&isDestructorCalled);
        QCOMPARE(obj->refCount(), 1);
        WeakPtr<DemoObject> weakPtr = obj;
        QCOMPARE(obj->refCount(), 1);

        if (auto ptr = weakPtr.lock())
        {
            QCOMPARE(obj->refCount(), 2);
        }
        QCOMPARE(obj->refCount(), 1);
    }
}

QTEST_MAIN(TestWeakPtr)

#include "TestWeakPtr.moc"

#endif
