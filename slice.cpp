
#include <algorithm>
#include<vector>
#include<map>


std::vector<std::pair<int,int>> get_slices(std::vector<int> &A)
{
   std::vector< std::pair<int,int> > slices;
   int previousIndex =  -1;

    for(unsigned int i = 0;  i < A.size(); i++)
    {
        if(A.at(i) >= 0)
        {
           std::pair<int,int> slice(i,i);
           slices.push_back(slice);

           if( ( previousIndex != -1)  && ((static_cast<int>(i) - previousIndex) == 1))
           {
             std::pair<int,int> slice(previousIndex,i);
             slices.push_back(slice);
           }
           previousIndex =static_cast<int>( i);
        }
    }
   return slices;
}


bool  is_slice_available(std::pair<int,int> slice ,const std::vector<std::pair<int,int>> &slices )

{
    bool result  = false;
    for(std::vector<std::pair<int,int>>::const_iterator iter  = slices.begin();
        iter != slices.end(); iter++)
    {
        if ( (( (*iter).first == slice.first) || ( (*iter).first == slice.second))
              || ( (*iter).second == slice.first ) || ((*iter).second == slice.second))
        {
            result  = true;
            break;
        }
    }
    return result;
}


std::vector<std::pair<int,int>> get_filter_slices(const std::vector<std::pair<int,int>> &slices ,
                                                   unsigned int upper_bounder)
{
  std::vector<std::pair<int,int>> result ;
  std::vector<int> takenIndex;

  for(unsigned int i=0; i < upper_bounder; i++)
  {
      if( i > upper_bounder)
          break;
       bool found = false;
       std::pair<int,int> slice  =  slices.at(i);
       found  = is_slice_available(slice,result );

       for(unsigned int j = i + 1; (j < upper_bounder) &&   (found  == false); j++)
       {
          std::pair<int,int> jslice  =  slices.at(j);

         if( slice.first == jslice.first)
         {
             result.push_back(jslice);
             found = true;
             break;
         }
       }

       if(found != true){
          result.push_back(slice);
       }
  }
  return result;
}

int sum_slices(const std::vector<std::pair<int,int>> &slices, std::vector<int> &values)
{
    int sum = (slices.size() > 0)? 0 : -1;

    for(std::vector<std::pair<int,int>>::const_iterator iter  = slices.begin();
        iter != slices.end(); iter++)
    {
       sum += values.at(static_cast<std::vector<int>::size_type>((*iter).first));

       if((*iter).first != ((*iter).second))
       {
         sum += values.at(static_cast<std::vector<int>::size_type>((*iter).second));
       }
    }
    return sum;
}


int solution(std::vector<int> values)
{
    std::vector<std::pair<int,int>>  results  =  get_slices(values);
    std::vector<std::pair<int,int>>  filters  =  get_filter_slices(results, values.size() -1);
    return sum_slices(filters,values);
}

//  [1, 2, -3, 4, 5, -6]
int main()
{
std::vector<int> vec ={1, 2, -3, 4, 5, -6};

printf("Result  =  %d \n",solution(vec));
getchar();

}
