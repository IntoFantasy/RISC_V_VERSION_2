//
// Created by ALIENWARE on 2021/7/1.
//
#include<queue>
#include"memory.h"
#include"order.h"
#ifndef CPU_RISC_V_CPU_H
#define CPU_RISC_V_CPU_H
class CPU{
private:
    unsigned int Register[32];
    int Register_occupied[32];//用于解决寄存器冲突
    order *current_order;
    void IF();
    void ID(order *order_fetch);
    void EX(order *order_fetch);
    void MEM(order *order_fetch);
    void WB(order  *order_fetch);

public:
    std::queue<order*>  ID_EXE;
    std::queue<order*>  EX_EXE;
    std::queue<order*>  MEM_EXE;
    std::queue<order*>  WB_EXE;//四个流水站,取指操作并不需要一个单独的队列
    bool IF_flag;//判断此时是否能进行命令的提取
    memory CPU_MEM;
    CPU(long long cap=1000000): CPU_MEM(cap){
        for(int i=0;i<32;++i){
            Register[i]=0;
            Register_occupied[i]=0;
        }
        IF_flag=true;
    };
    void RISC_V();
};


#endif //CPU_RISC_V_CPU_H
