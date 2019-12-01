class MyQueue {
    private:
        // store elements
        vector<int> data;       
        // a pointer to indicate the start position
        int p_start;            
    public:
        MyQueue():p_start{0}{}
        /** Qinsert an element into the queue. Return true if the operation is successful. */
        bool enQueue(int x) {
            data.push_back(x);
            return true;
        }
        /** Delete an element from the queue. Return true if the operation is successful. */
        bool deQueue() {
            if (isEmpty()) {
                return false;
            } 
            p_start++;
            return true;
        };
        /** Get the Qfront item from the queue. */
        int Qfront() {
            return data[p_start];
        };
        /** Checks whether the queue is empty or not. */
        bool isEmpty()  {
            return p_start >= data.size();
        }
};
class MycycleQueue{
    private:
        vector<int> data;
        const int queueLen;      //队列长度
        int queueCount;
        vector<int>::iterator Qfront;
        vector<int>::iterator Qinsert;
    public:
        MycycleQueue(int len):queueLen(len),queueCount(0){
            data.resize(5,0);
            Qfront = data.begin() ; 
            Qinsert = data.begin();
            }
        int Front(void)
        {
                return queueCount>0?*Qfront:INT_MAX;
        }
        int get_size()
        {
            return data.size();
        }
        bool enQueue(int val)
        {
            if(queueCount >= queueLen)
            {
                cerr<<"capacity is enough"<<endl;
                return false;
            }

            if(Qinsert == data.end()-1)
            {
                *Qinsert = val;
                Qinsert = data.begin();
            }
            else
            {
                *Qinsert = val;
                Qinsert++;
            }
            queueCount++;
            return true;
        }
        bool deQueue()
        {
            if(!queueCount)
            {
                return false;
            }
            if(Qfront == data.end()-1)
            {
                Qfront = data.begin();
            }
            else
            {
                Qfront++;
            }
            queueCount--;
            return true;
        }
        int rear()
        {
            if(queueCount<=0)
            {
                return INT_MAX;
            }
            if(Qinsert == data.begin())
            {
                return *data.end();
            }
            else
            {
                return *(Qinsert-1);
            }
        }
        bool isEmpty()
        {
            return queueCount==0?true:false;
        }
        bool isFull()
        {
            return queueLen == queueCount?true:false;
        }
        void print_queue()
        {
            int num = queueCount;
            auto i = Qfront;
            while(num)
            {
                if(i ==  data.end()-1)
                {
                    cout<<*i<<endl;
                    i = data.begin();
                }
                else
                {
                    cout<<*i<<endl;
                    i++;
                }
                num--;
            }
        }
};