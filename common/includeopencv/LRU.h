/*
 * =====================================================================================
 *
 *       Filename:  LRU.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/07/2015 05:56:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <string>
#include <map>
#include <assert.h>
#include "ipoint.h"

using namespace std;

class LRU
{
private:
    struct node
    {
        string key;
        IpVec *value;
        node *pre, *next;
        node(string t_key = "", IpVec *v = NULL):key(t_key),value(v),pre(NULL),next(NULL)
        {
        }
    };
    int m_capacity;
    map<string, node*>::iterator m_iter;
    map<string, node*> m_cache;
    node *m_head, *m_tail;
    enum {CPThreshold = 10}; 
private:
    void put2Head(node* p); 

public:
    LRU(const LRU&) {}
    LRU& operator= (const LRU &) {}
    LRU(int capacity = CPThreshold);
    ~LRU();
    
    IpVec* get(string key);
    IpVec* getWithoutChange(string key);
    void set(string key, IpVec* v);
    void getCache(vector<string> &cacheVec);
    void show();
};

#endif
