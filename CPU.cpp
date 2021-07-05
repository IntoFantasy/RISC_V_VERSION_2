//
// Created by ALIENWARE on 2021/7/1.
//
#include<map>
#include<iostream>
#include "CPU.h"
std::map<int,operation> orders={{55,lui},{23,auipc},{111,jal},{103,jalr},{99,B},{3,ld},{35,S},{19,I},{51,R},{15,fence},{115,I3}};
void CPU::IF() {
    int order_int=int(CPU_MEM.mem[CPU_MEM.get_PC()]);
    order_int%=128;
    operation op=orders[order_int];
    unsigned char *data=CPU_MEM.mem+CPU_MEM.get_PC();
    switch(op){
        case lui:{current_order=new Lui(data); break;}
        case auipc:{current_order=new Auipc(data);break;}
        case jal:{current_order=new Jal(data);IF_flag=false;break;}
        case jalr:{current_order=new Jalr(data);IF_flag=false;break;}
        case B:{current_order=new Control(data);IF_flag=false;break;}
        case ld:{current_order=new Load(data);break;}
        case S:{current_order=new Store(data);break;}
        case I:{current_order=new I_class(data);break;}
        case R:{current_order=new R_class(data);break;}
    }
}

void CPU::ID(order *order_fetch) {
    order_fetch->ID_exe(CPU_MEM,Register);
}

void CPU::EX(order *order_fetch) {
    order_fetch->Ex_exe(CPU_MEM,Register,IF_flag);
}

void CPU::MEM(order *order_fetch) {
    order_fetch->MEM_exe(CPU_MEM,Register);
}

void CPU::WB(order *order_fetch) {
    order_fetch->WB_exe(CPU_MEM,Register,Register_occupied);
}


void CPU::RISC_V() {
     while(true){
         if(!WB_EXE.empty()){
             order *order_tmp=WB_EXE.front();
             WB(order_tmp);
             WB_EXE.pop();
             delete order_tmp;
         }
         if(!MEM_EXE.empty()){
             order *order_tmp=MEM_EXE.front();
             MEM(order_tmp);
             MEM_EXE.pop();
             if(order_tmp->WB_need) WB_EXE.push(order_tmp);
             else delete order_tmp;
         }
         if(!EX_EXE.empty()){
             order *order_tmp=EX_EXE.front();
             EX(order_tmp);
             EX_EXE.pop();
             if(order_tmp->MEM_need) MEM_EXE.push(order_tmp);
             else{
                 if(order_tmp->WB_need) WB_EXE.push(order_tmp);
                 else delete order_tmp;
             }
         }
         if(!ID_EXE.empty()){
             order *order_tmp=ID_EXE.front();
             if(!order_tmp->ID_Judge(CPU_MEM,Register,Register_occupied)){
                 ID(order_tmp);
                 ID_EXE.pop();
                 if(order_tmp->EX_need)  EX_EXE.push(order_tmp);
                 else{
                     if(order_tmp->MEM_need) MEM_EXE.push(order_tmp);
                     else{
                         if(order_tmp->WB_need) WB_EXE.push(order_tmp);
                         else delete order_tmp;
                     }
                 }
             }
         }
         if(IF_flag){
             IF();
             ID_EXE.push(current_order);
             if(IF_flag) CPU_MEM.jump(4);
         }

     }
}

