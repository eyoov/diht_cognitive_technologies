#ifndef TEMPLATES_LIST_2015_03_06
#define TEMPLATES_LIST_2015_03_06

#include <exception>

namespace utility
{
    class MyException : public std::exception
    {

        char* message;

    public:
        MyException()
                : message(0)
        {}


        MyException(char* str)
                : message(str)
        {
            throw message;
        }

        void
        getException(char* str)
        {
            throw message;
        }

    };

    template<class T>
    class CSingleLinkedList
    {

        struct leaf
        {
            T data;
            leaf * pNext;

            leaf(T& _data, leaf * _pnext = 0)
                    : data(_data)
                    , pNext(_pnext)
            {}
        };

        leaf* m_pBegin;
        leaf* m_pEnd;

    public:
        class CIterator
        {
        private:
            leaf* m_pBegin;
            leaf* m_pCurrent;
        public:
            CIterator()
                    : m_pCurrent(0)
                    , m_pBegin(0)
            {}

            CIterator(leaf *p)
                    : m_pCurrent(p)
                    , m_pBegin(0)
            {}

            CIterator(const CIterator &src)
                    : m_pCurrent(src.m_pCurrent)
                    , m_pBegin(src.m_pBegin)
            {}

            ~CIterator()
            {}

            CIterator&
            operator= (const CIterator&  src)
            {
                if (this == &src)
                {
                    return *this;
                }
                m_pCurrent = src.m_pCurrent;
                m_pBegin = src.m_pBegin;
                return *this;
            }

            bool
            operator!= (const CIterator&  it) const
            {
                bool isHeadCompare(m_pCurrent != it.m_pCurrent);
                bool isCurrentPositionCompare(m_pBegin != 0 && m_pBegin != it.m_pBegin);
                return (isHeadCompare || isCurrentPositionCompare);
            }

            void
            operator++ ()
            {
                if (m_pBegin == 0 && m_pCurrent == 0)
                {
                    MyException("Iterator is out of list\n");
                }
                if (m_pBegin != 0)
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = 0;
                }
                else
                {
                    m_pCurrent = m_pCurrent->pNext;
                }
            }

            T&
            getData()
            {
                if (m_pCurrent == 0)
                {
                    MyException("Iterator is out of list\n");
                }
                return m_pCurrent->data;
            }

            T&
            operator* ()
            {
                if (m_pCurrent == 0)
                {
                    MyException("Iterator is out of list\n");
                }
                return m_pCurrent->data;
            }

            leaf*
            getLeaf()
            {
                return m_pCurrent;
            }

            void
            setLeaf(leaf* p)
            {
                if (p == m_pBegin || p == m_pCurrent)
                {
                    return;
                }
                m_pCurrent = p;
                m_pBegin = 0;
            }

            void
            setLeafPreBegin(leaf* p)
            {
                if (p == m_pBegin)
                {
                    return;
                }
                m_pCurrent = 0;
                if (m_pBegin == 0)
                {
                    m_pBegin = p;
                    return;
                }
                m_pBegin = p;
            }

            bool
            isValid()
            {
                if (m_pCurrent == 0 && m_pBegin == 0)
                {
                    return false;
                }
                return true;
            }
        };

        CSingleLinkedList()
                : m_pBegin(0)
                , m_pEnd(0)
        {}

        virtual ~CSingleLinkedList()
        {
            clear();
        }

        void
        pushBack(T& data)
        {
            leaf* newEnd = new leaf(data);
            if (m_pBegin == 0)
            {
                m_pBegin = newEnd;
                m_pEnd = newEnd;
            }
            else
            {
                m_pEnd->pNext = newEnd;
                m_pEnd = newEnd;
            }
        }

        void
        pushFront(T& data)
        {
            leaf* newBegin = new leaf(data);
            if (m_pBegin == 0)
            {
                m_pBegin = newBegin;
                m_pEnd = newBegin;
            }
            else
            {
                newBegin->pNext = m_pBegin;
                m_pBegin = newBegin;
            }
        }

        T
        popFront()
        {
            if (m_pBegin == 0)
            {
                MyException("The list is empty\n");
            }
            T returnValue = m_pBegin->data;
            leaf* begin = m_pBegin;
            m_pBegin = m_pBegin->pNext;
            delete begin;
            if (m_pBegin == 0)
            {
                m_pEnd = 0;
            }
            return returnValue;
        }

        void
        erase(CIterator& it)
        {
            if (!it.isValid())
            {
                MyException("Iterator is not valid\n");
            }
            leaf* pdelete = it.getLeaf();
            if (pdelete == m_pBegin)
            {
                m_pBegin = m_pBegin->pNext;
                delete pdelete;
                if (m_pBegin == 0)
                {
                    m_pEnd = 0;
                }
                it.setLeafPreBegin(m_pBegin);
            }
            else
            {
                leaf* pcurrent = m_pBegin;
                while (pcurrent->pNext != pdelete && pcurrent != 0)
                {
                    pcurrent = pcurrent->pNext;
                }
                if (pcurrent == 0)
                {
                    MyException("Iterator is not valid\n");
                }
                pcurrent->pNext = pcurrent->pNext->pNext;
                delete pdelete;
                it.setLeaf(pcurrent);
            }
        }

        int
        getSize()
        {
            int size = 0;
            leaf* current = m_pBegin;
            while (current != 0)
            {
                current = current->pNext;
                ++size;
            }
            return size;
        }

        void
        clear()
        {
            leaf* current = m_pBegin;
            while (current != 0)
            {
                m_pBegin = current->pNext;
                delete current;
                current = m_pBegin;
            }
            m_pBegin = 0;
            m_pEnd = 0;
        }

        CIterator
        begin()
        {
            return CIterator(m_pBegin);
        }

        CIterator
        end()
        {
            return CIterator(m_pEnd);
        }

    };

    template<class T>
    class CQueue
    {

        struct leaf
        {
            T data;
            leaf* pNext;
            leaf(T& _data, leaf* _pnext = NULL)
                    : data(_data)
                    , pNext(_pnext)
            {}
        };

        leaf* m_pBegin;
        leaf* m_pEnd;

    public:
        CQueue()
                : m_pBegin(0)
                , m_pEnd(0)
        {}

        virtual ~CQueue()
        {
            clear();
        }

        void
        InQueue(T& data)
        {
            leaf* newLeaf = new leaf(data, 0);
            if (m_pBegin == 0)
            {
                m_pBegin = newLeaf;
                m_pEnd = newLeaf;
                return;
            }
            m_pEnd->pNext = newLeaf;
            m_pEnd = newLeaf;
        }

        T
        DeQueue()
        {
            if (m_pBegin == 0)
            {
                MyException("The queue is empty\n");
            }
            T Value = m_pBegin->data;
            leaf* pBegin = m_pBegin;
            if (m_pEnd == pBegin)
            {
                m_pEnd = 0;
            }
            m_pBegin = m_pBegin->pNext;
            delete pBegin;
            return Value;
        }

        bool
        isQueueEmpty()
        {
            if (m_pBegin == 0)
            {
                return true;
            }
            return false;
        }

        int
        getSize()
        {
            int size = 0;
            leaf* pIter = m_pBegin;
            while (pIter != 0)
            {
                ++size;
                pIter = pIter->pNext;
            }
            return size;
        }

        void
        clear()
        {
            leaf* pIter = m_pBegin;
            while (pIter != 0)
            {
                pIter = pIter->pNext;
                delete m_pBegin;
                m_pBegin = pIter;
            }
            m_pBegin = 0;
            m_pEnd = 0;
        }

    };

    template<class T>
    class CDoublyLinkedList
    {

        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data, leaf * _pprev = 0, leaf * _pnext = 0)
                    : data(_data)
                    , pprev(_pprev)
                    , pnext(_pnext)
            {}
        };

        leaf* m_pBegin;
        leaf* m_pEnd;

    public:
        class CIterator
        {
            leaf* m_pBegin;
            leaf* m_pCurrent;
            leaf* m_pEnd;

        public:
            CIterator()
                    : m_pBegin(0)
                    , m_pCurrent(0)
                    , m_pEnd(0)
            {}

            CIterator(leaf *p)
                    : m_pBegin(0)
                    , m_pCurrent(p)
                    , m_pEnd(0)
            {}

            CIterator(const CIterator &src)
                    : m_pBegin(src.m_pBegin)
                    , m_pCurrent(src.m_pCurrent)
                    , m_pEnd(src.m_pEnd)
            {}

            ~CIterator()
            {}

            CIterator&
            operator = (const CIterator&  src)
            {
                if (this == &src)
                {
                    return *this;
                }
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pEnd = src.m_pEnd;
                return *this;
            }

            bool
            operator != (const CIterator&  it) const
            {
                bool equalityCurrentIterator(m_pCurrent != it.m_pCurrent);
                bool equalityBeginIterator(m_pBegin!= 0 &&m_pBegin != it.m_pBegin);
                bool equalityEndIterator(m_pEnd != 0 && m_pEnd != it.m_pEnd);
                return (equalityCurrentIterator || equalityBeginIterator || equalityEndIterator);
            }

            void
            operator++ ()
            {
                if (!isValid())
                {
                    MyException("Iterator is invalid\n");
                }
                if (m_pBegin!= 0)
                {
                    m_pCurrent =m_pBegin;
                    m_pBegin= 0;
                    return;
                }
                if (m_pEnd != 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                if (m_pCurrent->pnext == 0)
                {
                    setLeafPostEnd(m_pCurrent);
                    return;
                }
                m_pCurrent = m_pCurrent->pnext;
            }

            void
            operator--()
            {
                if (!isValid())
                {
                    MyException("Iterator is invalid\n");
                }
                if (m_pEnd != 0)
                {
                    m_pCurrent = m_pEnd;
                    m_pEnd = 0;
                    return;
                }
                if (m_pBegin!= 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                if (m_pCurrent->pprev == 0)
                {
                    setLeafPreBegin(m_pCurrent);
                    return;
                }
                m_pCurrent = m_pCurrent->pprev;
            }

            T&
            getData()
            {
                if (!isValid())
                {
                    MyException("Iterator is invalid\n");
                }
                if (m_pCurrent == 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                return m_pCurrent->data;
            }

            T&
            operator* ()
            {
                return getData();
            }

            leaf*
            getLeaf()
            {
                return m_pCurrent;
            }

            void
            setLeaf(leaf* p)
            {
                m_pBegin= 0;
                m_pCurrent = p;
                m_pEnd = 0;
            }

            void
            setLeafPreBegin(leaf* p)
            {
                m_pBegin= p;
                m_pCurrent = 0;
                m_pEnd = 0;
            }

            void
            setLeafPostEnd(leaf* p)
            {
                m_pBegin= 0;
                m_pCurrent = 0;
                m_pEnd = p;
            }

            bool
            isValid()
            {
                return (m_pCurrent != 0 ||m_pBegin != 0 || m_pEnd != 0);
            }

            bool
            isPreBegin()
            {
                if (m_pBegin!= 0)
                {
                    return true;
                }
                return false;
            }

        };


    public:

        CDoublyLinkedList()
                :m_pBegin(0)
                , m_pEnd(0)
        {};

        virtual ~CDoublyLinkedList()
        {
            clear();
        };

        void
        pushBack(T& data)
        {
            leaf* newLeaf = new leaf(data, m_pEnd, 0);
            if (m_pBegin== 0)
            {
                m_pBegin= newLeaf;
                m_pEnd = newLeaf;
                return;
            }
            m_pEnd->pnext = newLeaf;
            m_pEnd = newLeaf;
        }

        T
        popBack()
        {
            if (m_pBegin== 0)
            {
                MyException("The list is empty\n");
            }
            T value = m_pEnd->data;
            leaf* pdelete = m_pEnd;
            m_pEnd = m_pEnd->pprev;
            m_pEnd->pnext = 0;
            if (m_pBegin== pdelete)
            {
                m_pBegin= 0;
            }
            delete pdelete;
            return value;
        }

        void
        pushFront(T& data)
        {
            leaf* newLeaf = new leaf(data, 0,m_pBegin);
            if (m_pBegin== 0)
            {
                m_pBegin= newLeaf;
                m_pEnd = newLeaf;
                return;
            }
            m_pBegin->pprev = newLeaf;
            m_pBegin= newLeaf;
        }

        T
        popFront()
        {
            if (m_pBegin == 0)
            {
                MyException("The list is empty\n");
            }
            T value =m_pBegin->data;
            leaf* pdelete =m_pBegin;
            m_pBegin=m_pBegin->pnext;
            if (!m_pBegin == 0)
            {
                m_pBegin->pprev = 0;
            }
            if (m_pEnd == pdelete)
            {
                m_pEnd = 0;
            }
            delete pdelete;
            return value;
        }

        void
        erase(CIterator& it)
        {
            if (!it.isValid())
            {
                MyException("Iterator is invalid\n");
            }
            leaf* pdelete = it.getLeaf();
            if (pdelete == 0)
            {
                MyException("Iterator is out of list\n");
            }
            if (pdelete ==m_pBegin)
            {
                m_pBegin=m_pBegin->pnext;
                m_pBegin->pprev = 0;
                delete pdelete;
                if (m_pBegin== 0)
                {
                    m_pEnd = 0;
                }
                it.setLeafPreBegin(m_pBegin);
            }
            else
            {
                leaf* pcurrent = m_pBegin->pnext;
                while (pcurrent != pdelete && pcurrent != 0)
                {
                    pcurrent = pcurrent->pnext;
                }
                if (pcurrent == 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                pcurrent->pprev->pnext = pcurrent->pnext;
                if (pcurrent->pnext != 0)
                {
                    pcurrent->pnext->pprev = pcurrent->pprev;
                }
                if (pcurrent == m_pEnd)
                {
                    m_pEnd = pcurrent->pprev;
                }
                pcurrent = pcurrent->pprev;
                delete pdelete;
                it.setLeaf(pcurrent);
            }
        }

        void
        eraseAndNext(CIterator& it)
        {
            if (!it.isValid())
            {
                MyException("Iterator is invalid\n");
            }
            leaf* pdelete = it.getLeaf();
            if (pdelete == m_pEnd)
            {
                m_pEnd = m_pEnd->pprev;
                m_pEnd->pnext = 0;
                delete pdelete;
                if (m_pEnd == 0)
                {
                    m_pBegin= 0;
                }
                it.setLeafPostEnd(m_pEnd);
            }
            else
            {
                leaf* pcurrent =m_pBegin;
                while (pcurrent != pdelete && pcurrent != 0)
                {
                    pcurrent = pcurrent->pnext;
                }
                if (pcurrent == 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                pcurrent->pnext->pprev = pcurrent->pprev;
                if (pcurrent->pprev != 0)
                {
                    pcurrent->pprev->pnext = pcurrent->pnext;
                }
                if (pcurrent ==m_pBegin)
                {
                    m_pBegin= pcurrent->pnext;
                }
                pcurrent = pcurrent->pnext;
                delete pdelete;
                it.setLeaf(pcurrent);
            }
        }

        void
        insert(CIterator& it, T& data)
        {
            if (!it.isValid())
            {
                MyException("Iterator is invalid\n");
            }
            leaf* pinsert = it.getLeaf();
            if (pinsert == 0)
            {
                if (it.isPreBegin())
                {
                    leaf* newLeaf = new leaf(data, 0,m_pBegin);
                    m_pBegin->pprev = newLeaf;
                    m_pBegin= newLeaf;
                    it.setLeafPreBegin(newLeaf);
                    return;
                }
                else
                {
                    MyException("Iterator is out of the list\n");
                }
            }

            leaf* pcurrent =m_pBegin;
            while (pcurrent != pinsert && pcurrent != 0)
            {
                pcurrent = pcurrent->pnext;
            }
            if (pcurrent == 0)
            {
                MyException("Iterator is out of the list\n");
            }
            if (pcurrent == m_pEnd)
            {
                leaf* newLeaf = new leaf(data, m_pEnd, 0);
                m_pEnd->pnext = newLeaf;
                m_pEnd = newLeaf;
                return;
            }
            leaf* newLeaf = new leaf(data, pcurrent, pcurrent->pnext);
            pcurrent->pnext->pprev = newLeaf;
            pcurrent->pnext = newLeaf;
        }

        int
        getSize()
        {
            int size = 0;
            leaf* pcurrent =m_pBegin;
            while (pcurrent != 0)
            {
                size++;
                pcurrent = pcurrent->pnext;
            }
            return size;
        }

        void
        clear()
        {
            leaf* pcurrent =m_pBegin;
            while (pcurrent != 0)
            {
                m_pBegin= pcurrent->pnext;
                delete pcurrent;
                pcurrent =m_pBegin;
            }
            m_pBegin= 0;
            m_pEnd = 0;
        }

        CIterator begin()
        {
            return CIterator(m_pBegin);
        }

        CIterator end()
        {
            CIterator it;
            it.setLeafPostEnd(m_pEnd);
            return it;
        }
    };

    template<class T>
    class CDoublyLinkedListFictive
    {

        struct leaf
        {
            T data;
            leaf* pnext, *pprev;

            leaf()
                    : data(T())
                    , pnext(0)
                    , pprev(0)
            {}

            leaf(T& _data, leaf* _pprev, leaf* _pnext)
                    : data(_data)
                    , pprev(_pprev)
                    , pnext(_pnext)
            {
            }
        };

        leaf* m_pNil;

    public:
        class CIterator
        {
            leaf* m_pBegin;
            leaf* m_pCurrent;
            leaf* m_pNil;
            leaf* m_pEnd;
        public:
            CIterator ()
                    : m_pBegin(0)
                    , m_pCurrent(0)
                    , m_pNil(0)
                    , m_pEnd(0)
            {}

            CIterator (leaf *pNil, leaf *p)
                    : m_pBegin(0)
                    , m_pCurrent(p)
                    , m_pNil(pNil)
                    , m_pEnd(0)
            {}

            CIterator (const CIterator &src)
                    : m_pBegin(src.m_pBegin)
                    , m_pCurrent(src.m_pCurrent)
                    , m_pNil(src.m_pNil)
                    , m_pEnd(src.m_pEnd)
            {}

            ~CIterator ()
            {}

            CIterator&
            operator = (const CIterator& src)
            {
                if (this == &src)
                {
                    return *this;
                }
                m_pBegin = src.m_pBegin;
                m_pCurrent = src.m_pCurrent;
                m_pNil = src.m_pNil;
                m_pEnd = src.m_pEnd;
                return *this;
            }

            bool
            operator != (const CIterator&  it) const
            {
                bool fictiveCompare(m_pNil != it.m_pNil);
                bool currentCompare(m_pCurrent != it.m_pCurrent);
                bool beginCompare(m_pBegin != 0 && m_pBegin != it.m_pBegin);
                bool endCompare(m_pEnd != 0 && m_pEnd != it.m_pEnd);
                return (fictiveCompare || currentCompare
                        || beginCompare || endCompare);
            }

            void
            operator++ ()
            {
                if (m_pBegin != 0)
                {
                    m_pCurrent = m_pBegin;
                    m_pBegin = 0;
                    return;
                }
                if (m_pEnd != 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                if (m_pCurrent->pnext == m_pNil)
                {
                    m_pEnd = m_pCurrent;
                    m_pCurrent = 0;
                }
                else
                {
                    m_pCurrent = m_pCurrent->pnext;
                }
            }

            void
            operator-- ()
            {
                if (m_pBegin != 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                if (m_pEnd != 0)
                {
                    m_pCurrent = m_pEnd;
                    m_pEnd = 0;
                    return;
                }
                if (m_pCurrent->pprev == m_pNil)
                {
                    m_pBegin = m_pCurrent;
                    m_pCurrent = 0;
                }
                else
                {
                    m_pCurrent = m_pCurrent->pprev;
                }
            }

            T&
            getData ()
            {
                if (m_pBegin != 0 || m_pEnd != 0)
                {
                    MyException("Iterator is out of the list\n");
                }
                return m_pCurrent->data;
            }

            T&
            operator* ()
            {
                return getData();
            }

            leaf*
            getLeaf ()
            {
                return m_pCurrent;
            }

            bool
            isPreBegin ()
            {
                return (m_pBegin != 0);
            }

            void
            setLeaf (leaf* p)
            {
                m_pCurrent = p;
                m_pBegin = 0;
                m_pEnd = 0;
            }

            void
            setLeafPreBegin (leaf* p)
            {
                m_pCurrent = 0;
                m_pBegin = p;
                m_pEnd = 0;
            }

            void
            setLeafPostEnd (leaf* p)
            {
                m_pCurrent = 0;
                m_pBegin = 0;
                m_pEnd = p;
            }

            bool
            isValid ()
            {
                return (m_pCurrent != 0 || m_pBegin != 0 || m_pEnd != 0);
            }
        };


    public:
        CDoublyLinkedListFictive ()
        {
            m_pNil = new leaf();
            m_pNil->pnext = m_pNil;
            m_pNil->pprev = m_pNil;
        }

        virtual ~CDoublyLinkedListFictive ()
        {
            clear();
            delete m_pNil;
        }

        void
        pushBack (T& data)
        {
            leaf* newEnd = new leaf(data, m_pNil->pprev, m_pNil);
            m_pNil->pprev->pnext = newEnd;
            m_pNil->pprev = newEnd;
        }

        T
        popBack ()
        {
            if (m_pNil->pprev == m_pNil)
            {
                MyException("Empty child\n");
            }
            leaf* pdelete = m_pNil->pprev;
            T returnValue = pdelete->data;
            pdelete->pprev->pnext = m_pNil;
            m_pNil->pprev = pdelete->pprev;
            delete pdelete;
            return returnValue;
        }

        void
        pushFront (T& data)
        {
            leaf* newBegin = new leaf(data, m_pNil, m_pNil->pnext);
            m_pNil->pnext->pprev = newBegin;
            m_pNil->pnext = newBegin;
        }

        T
        popFront ()
        {
            if (m_pNil->pnext == m_pNil)
            {
                MyException("The list is empty\n");
            }
            leaf* pdelete = m_pNil->pnext;
            T returnValue = pdelete->data;
            pdelete->pnext->pprev = m_pNil;
            m_pNil->pnext = pdelete->pnext;
            delete pdelete;
            return returnValue;
        }

        void
        erase (CIterator& it)
        {
            tryToFind(it);
            leaf* pdelete = it.getLeaf();
            leaf* pcurrent = pdelete->pprev;
            pcurrent->pnext = pdelete->pnext;
            pdelete->pnext->pprev = pcurrent;
            delete pdelete;
            if (pcurrent == m_pNil)
            {
                it.setLeafPreBegin(pcurrent->pnext);
            }
            else
            {
                it.setLeaf(pcurrent);
            }
        }

        void
        eraseAndNext (CIterator& it)
        {
            tryToFind(it);
            leaf* pdelete = it.getLeaf();
            leaf* pcurrent = pdelete->pnext;
            pcurrent->pprev = pdelete->pprev;
            pdelete->pprev->pnext = pcurrent;
            delete pdelete;
            if (pcurrent == m_pNil)
            {
                it.setLeafPostEnd(pcurrent->pprev);
            }
            else
            {
                it.setLeaf(pcurrent);
            }
        }

        void
        insert (CIterator& it, T& data)
        {
            if (!it.isValid())
            {
                MyException("Iterator is invalid\n");
            }
            leaf* pinsert = it.getLeaf();
            if (pinsert == 0)
            {
                if (it.isPreBegin())
                {
                    pushFront(data);
                    it.setLeafPreBegin(m_pNil->pnext);
                    return;
                }
                else
                {
                    MyException("Iterator is invalid\n");
                }
            }
            if (pinsert == m_pNil)
            {
                pushFront(data);
                it.setLeafPreBegin(m_pNil->pnext);
                return;
            }
            if (pinsert == m_pNil->pprev)
            {
                pushBack(data);
                return;
            }
            leaf* newLeaf = new leaf(data, pinsert, pinsert->pnext);
            pinsert->pnext->pprev = newLeaf;
            pinsert->pnext = newLeaf;
        }

        int
        getSize ()
        {
            int size = 0;
            leaf* pcurrent = m_pNil->pnext;
            while (pcurrent != m_pNil)
            {
                ++size;
                pcurrent = pcurrent->pnext;
            }
            return size;
        }

        void
        clear ()
        {
            leaf* pcurrent = m_pNil->pnext;
            while (pcurrent != m_pNil)
            {
                pcurrent = pcurrent->pnext;
                delete pcurrent->pprev;
            }
            m_pNil->pnext = m_pNil;
            m_pNil->pprev = m_pNil;
        }

        CIterator
        begin ()
        {
            return CIterator(m_pNil, m_pNil->pnext);
        }

        CIterator
        end ()
        {
            CIterator it(m_pNil, 0);
            it.setLeafPostEnd(m_pNil->pprev);
            return it;
        }

        void
        tryToFind (CIterator& it)
        {
            if (!it.isValid())
            {
                MyException("Iterator is invalid\n");
            }
            leaf* pfind = it.getLeaf();
            if (pfind == 0)
            {
                MyException("Iterator is out of the list\n");
            }
            leaf* pcurrent = m_pNil->pnext;
            while (pcurrent != m_pNil && pcurrent != pfind)
            {
                pcurrent = pcurrent->pnext;
            }
            if (pcurrent == m_pNil)
            {
                MyException("Iterator is out of the list\n");
            }
        }
    };
};
#endif //#ifndef TEMPLATES_LIST_2015_03_06