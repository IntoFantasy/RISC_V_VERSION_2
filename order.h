//
// Created by ALIENWARE on 2021/6/30.
//
#include "memory.h"
#ifndef CPU_RISC_V_ORDER_H
#define CPU_RISC_V_ORDER_H
enum operation{lui,auipc,jal,jalr,B,ld,S,I,R,I3,fence};       //仅仅是大类区分（由最后七位决定）,具体分类到exe再执行
class order{
protected:
    int code[4];     //以四位十进制存储
public:
    order()=default;
    order(unsigned char *data);
    virtual bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc){return false;}//判断寄存器是否被占用,同时兼具解析立即数和寄存器地址的功能
    virtual void ID_exe(memory &MEM,unsigned int *reg){return;};
    bool EX_need;
    virtual void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag){return;};
    bool MEM_need;
    virtual void MEM_exe(memory &MEM,unsigned int *reg){return;};
    bool WB_need;
    virtual void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc){return;};
    operation op;
    bool Decoded;//判断是否已被解析
};
class Lui:public order{
private:
    int imm;//立即数
    int rd_id;//目标寄存器的地址
    int rd_data;
public:
    Lui(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class Auipc:public order{
private:
    int imm;
    int rd_id;
    int rd_data;
public:
    Auipc(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class Jal:public order{
private:
    int imm;
    int rd_id;
    unsigned int rd_data;
public:
    Jal(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class Jalr:public order{
private:
    int imm;
    int rd_id;
    unsigned int rd_data;
    int rs_id;
    unsigned int rs_data;
public:
    Jalr(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class Load:public order{
private:
    int func3;
    int rd_id;
    unsigned int rd_data;
    int rs_id;
    unsigned int rs_data;
    int imm;
    int address;
public:
    Load(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void MEM_exe(memory &MEM,unsigned int *reg) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;

};
class Control:public order{
private:
    int imm;
    int rs_id1;
    unsigned int rs_data1;
    int rs_id2;
    unsigned int rs_data2;
    int func3;
public:
    Control(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
};
class I_class:public order{
private:
    int imm;
    int rd_id;
    unsigned int rd_data;
    int rs_id1;
    unsigned int rs_data1;
    int func3;
    int func7;
    int shamt;
public:
    I_class(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class R_class:public order{
private:
    int rs_id1;
    unsigned int rs_data1;
    int rs_id2;
    unsigned int rs_data2;
    int rd_id;
    unsigned int rd_data;
    int func3;
    int func7;
public:
    R_class(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void WB_exe(memory &MEM,unsigned int *reg,int *reg_oc) override;
};
class Store:public order{
private:
    int rs_id1;
    unsigned int rs_data1;
    int rs_id2;
    unsigned int rs_data2;
    int func3;
    int imm;
    int address;
public:
    Store(unsigned char *data);
    bool ID_Judge(memory &MEM,unsigned int *reg,int *reg_oc) override;
    void ID_exe(memory &MEM,unsigned int *reg) override;
    void Ex_exe(memory &MEM,unsigned int *reg,bool &IF_flag) override;
    void MEM_exe(memory &MEM,unsigned int *reg) override;
};
#endif //CPU_RISC_V_ORDER_H
