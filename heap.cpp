#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <ctime>
#include <cassert>
#include <cmath>
using namespace std;

class Max_heap{
    public:
    Max_heap(int size)
    {
        m_buffer   = (int *)malloc((size+1)*sizeof(int));
        m_cur_size = 0;
        m_max_size = size;
    }
    Max_heap(int *buffer, int size)
    {
        m_cur_size = size;
        m_max_size = size;
        //分配内存
        m_buffer   = (int *)malloc((size+1)*sizeof(int));
        memcpy(m_buffer, buffer, (size+1)*sizeof(int));

        //shift down
        for (int i=size/2; i>=1; i--)
        {
            shift_down(i);
        }

    }
    ~Max_heap(void)
    {
        if (m_buffer != NULL)
        {
            free(m_buffer);
        }
    }
    int get_cur_size(void)
    {
        return (m_cur_size);
    }
    void print(void)
    {
        printf("\n");

        for(int i=1; i<=m_cur_size; i++)
        {
            printf("%d ", m_buffer[i]);
        }

        printf("\n");
        testPrint();
    }
    int insert(int e)
    {
        if (m_cur_size>=m_max_size)
        {
            return (-1);
        }
        
        m_buffer[++m_cur_size] = e;

        shift_up(m_cur_size);
    }

    int exact(void)
    {
        int res = m_buffer[1];

        swap(m_buffer+1, m_buffer+m_cur_size);
        m_cur_size--;

        shift_down(1);


        return(res);
    }
    int empty(void)
    {
        return(m_cur_size<1?1:0);
    }
    private:
    int *m_buffer  ;
    int  m_max_size;
    int  m_cur_size;

    int size(void)
    {
	    return(m_cur_size);
    }

    void swap(int *x, int *y)
    {
        int tmp = *x; 
        *x      = *y;
        *y      = tmp;
    }

    int shift_up(int index)
    {
        while(index > 1)
        {
            int parent = index/2;
            if (m_buffer[index] > m_buffer[parent])
            {
                swap(m_buffer+index, m_buffer+parent);
            }
            index /= 2;
        }
        return(0);
    }
    void shift_down(int index)
    {
       int i = index;
       while(2*i<m_cur_size)
       {
           int j = 0;
        
           if (i*2+1<m_cur_size)
           {
               // 有左孩子，比较左右孩子取较大者
               j =  m_buffer[i*2]>m_buffer[i*2+1]? i*2:i*2+1;
           }
           else
           {  
              // 无左孩子，取右孩子
              j = 2*i;
           }
           swap(m_buffer + i, m_buffer + j);
           i = j;
       }

    }

    void testPrint(){

        if( size() >= 100 ){
            cout<<"Fancy print can only work for less than 100 int";
            cout<<"The Heap size is: "<<size()<<endl;
            return;
        }

      

        cout<<"The Heap size is: "<<size()<<endl;
        cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            cout<<m_buffer[i]<<" ";
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        // 找出当前
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = m_cur_size-(int)pow(2,level)+1>int(pow(2,level))?int(pow(2,level)):m_cur_size-(int)pow(2,level)+1;
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( m_buffer[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }

    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

};

int main(int argc, char **argv)
{
#if 0
    Max_heap heap = Max_heap(50);
    for (int i=0; i<31; i++)
    {
      heap.insert(i);
    }
#else
    int buffer[31] = {};
    for (int i = 0; i<31; i++)
    {
        buffer[i]=i;
    }
    Max_heap heap = Max_heap(buffer, 31);
#endif
    printf("cur size = %d\n", heap.get_cur_size());
    heap.print();
    printf("\n");
    while(!heap.empty())
    {
        printf("%d ", heap.exact());
    }
    printf("\n");
    return(0);
}
