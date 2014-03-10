#ifndef _CRANGEPRINT_TREE_HPP_
#define _CRANGEPRINT_TREE_HPP_

#include "CBSAvlTree.hpp"

template<class type>
class CRangePrintTree : public CBSAvlTree<type>
{
public:
    void RangePrint(type lVal,type rVal);
private:
    void cmpLeft(nodeType<type>* p,type val);
    void cmpRight(nodeType<type>* p,type val);
};

template<class type>
void CRangePrintTree<type>::RangePrint(type lVal, type rVal)
{
    nodeType<type>* current;
    if(this->IsEmpty())
    {
        std::cout<<"No elements in this tree!"<<std::endl;
        return;
    }

    current=this->m_root;


    if(this->m_cmpRoute(&current->elem,&lVal)==SMALLER)
    {
        while((current!=NULL)&&(this->m_cmpRoute(&current->elem,&lVal)==SMALLER))
        {
            current=current->rLink;
        }
    }
    else if(this->m_cmpRoute(&current->elem,&rVal)==LARGER)
    {
        while((current!=NULL)&&(this->m_cmpRoute(&current->elem,&rVal)==LARGER))
        {
            current=current->lLink;
        }
    }

    /*
    *   if the is located between the range of left value and right value
    *   Compare its left child with left value,
    *   Compare its right child with right value;
    */


    if(current!=NULL)
    {
    	this->m_printRoute(current->elem);
        cmpLeft(current->lLink,lVal);
        cmpRight(current->rLink,rVal);
    }


}

template<class type>
void CRangePrintTree<type>::cmpLeft(nodeType < type > * p, type val)
{
    cmp_t result;
    if(p==NULL)
        return;


    if((result=this->m_cmpRoute(&p->elem,&val))==LARGER)
    {
        /*
        *   if element larger than left range, search its left child
        *   and print its right child
        */
        cmpLeft(p->lLink,val);
        this->m_printRoute(p->elem);
        printf("[%s]\n",__FUNCTION__);
        this->preorder(p->rLink);
    }
    else if(result==SMALLER)
    {
    	cmpLeft(p->rLink,val);
    }
    else if(result==EQUAL)
    {
        this->preorder(p->rLink);
    }

    return;
}


template<class type>
void CRangePrintTree<type>::cmpRight(nodeType < type > * p, type val)
{
    cmp_t result;
    if(p==NULL)
        return;


    if((result=this->m_cmpRoute(&p->elem,&val))==SMALLER)
    {
        /*
        *   if element smaller than right range, search its right child
        *   and print its right child
        */
        cmpRight(p->rLink,val);
        this->m_printRoute(p->elem);
        printf("[%s]\n",__FUNCTION__);
        this->preorder(p->lLink);
    }
    else if(result==SMALLER)
    {
    	cmpRight(p->lLink,val);
    }
    else if(result==EQUAL)
    {
        this->preorder(p->lLink);
    }

    return;

}

#endif
