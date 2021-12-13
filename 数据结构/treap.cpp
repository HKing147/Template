/*
 * @Author: ACCXavier
 * @Date: 2021-06-17 00:53:47
 * @LastEditTime: 2021-06-17 14:28:12
 * Bilibili:https://space.bilibili.com/7469540
 * 题目地址:https://www.acwing.com/problem/content/description/255/
 * @keywords: Treap 平衡树
 */
#include <iostream>
using namespace std;

const int N = 100010, INF = 1e8;

int n;

struct Node {
    int l, r;  // 左右儿子
    int key;   // 二叉搜索树权值
    int val;   // 大根堆的随机权值
    int cnt;   // 当前节点的key的重复个数
    int size;  // 当前节点的子孙节点个数
} tr[N];    //空间O(N)

//Treap在以关键码构成二叉搜索树的同时，还满足堆的性质
//且堆的权重随机,这使得treap的期望复杂度是logn

int root, idx;// 根节点序号 和 序号

//更新父节点size信息,用儿子节点
void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

//创建一个叶节点
int get_node(int key){
    tr[++ idx].key = key;
    tr[idx].val = rand();//随机值
    tr[idx].cnt = tr[idx].size = 1;//cnt,size
    return idx;
}

//初始化平衡树 左右哨兵 
//y总:如果查询的结果可能不存在，那加上哨兵之后可以保证查询的结果一定存在，
//就不需要在查询过程中特判无解的情况了。
void build(){
    get_node(-INF),get_node(INF);
    root = 1,tr[1].r = 2;//+inf > -inf,+inf在-inf右边
    pushup(root);//更新root的size
}

//右旋
void zig(int &p){ //根变了,传引用
// 旋转的时候传root,root会变化,我们希望root还是真正的root,故用root
// p始终指向根


    int q = tr[p].l; //q是左儿子
    tr[p].l = tr[q].r,//p的左儿子是q的右儿子
    tr[q].r = p,//q的右儿子是p
    p = q;//p再变回根
    pushup(tr[p].r),//更新p.r

    pushup(p);//不需要更新p是因为看着右旋图,右旋之前y左是A+B,y右是C,旋过之后实际上y左是A,y右是B+C,
    //但是不更新p,由于有 tr[q].r = p,相当于y的size由左侧的A+B和右侧的C构成,不影响最终size
    //但是p的r要更新,因为r由B和C构成(r旋前只有C)

}

//左旋
void zag(int &p){
    int q = tr[p].r;
    tr[p].r = tr[q].l;//p的右儿子是q的左儿子
    tr[q].l = p;//q的左儿子是p
    p = q;//p再变回根
    pushup(tr[p].l);
    pushup(p);    

}

//插入值key,从根开始

void insert(int &p,int key)//p是每一层根节点的指针
{
    if(!p) p = get_node(key);// 不存在根,则构造(最底层时构造节点)
    //由于这里是引用,传过来的是A节点的左或右,get_node之后A节点的左和右就是get_node的返回值idx,故完成了连接


    else if (tr[p].key == key)tr[p].cnt ++; // 刚好key和p的key相等, 则直接增加cnt
    else if (tr[p].key > key){ // 当前节点值大于key,说明应该在左子树插入
        insert(tr[p].l,key);

        //由于在左子树插入,插入左侧后左子树val可能大于根节点,左大右旋,保证堆的性质
        if(tr[tr[p].l].val > tr[p].val) zig(p);
    }
    else{
        insert(tr[p].r,key);
        //右大左旋
        if(tr[tr[p].r].val > tr[p].val) zag(p);
    }
    pushup(p);//p是每一层的根,指针,自底向上更新p   
}

void remove(int &p,int key){
    if(!p) return ;//不存在要删除的值
    if(tr[p].key == key){ //要删除当前节点
        if(tr[p].cnt > 1)tr[p].cnt --;
        else if (tr[p].l || tr[p].r){ // 当前节点只有一个可以且有左儿子或右儿子
        //注意rand函数>=0,左子树为空等价于idx = 0的点,其val为0

            if(!tr[p].r||tr[tr[p].l].val > tr[tr[p].r].val){
            //只存在左儿子(左val>右val_0)或左val>右val 
                zig(p);//左val大右旋
                remove(tr[p].r,key);
            }
            else//若存在右儿子且左val<右val 
            //(左儿子也可能不存在, 不存在的话左儿子的val就是0,肯定<=右儿子的val(val最小为0),这个模板隐含了判存在操作)
            {
                zag(p);//右大左旋
                remove(tr[p].l,key);
            }
        }
        else //不存在左右子树,是叶子节点
            p = 0;//空节点

    }else if (tr[p].key > key)remove(tr[p].l,key);//去左侧删
    else remove(tr[p].r,key);//右侧删
    pushup(p);// 自底向上更新p的size
}

//没有修改,不需要引用

int get_rank_by_key(int p, int key)    // 通过数值找排名
{
    if (!p) return 0;
    if (tr[p].key == key) return tr[tr[p].l].size + 1;//左子树的size + 1(同样的数值中最靠左的)
    if (tr[p].key > key)return get_rank_by_key(tr[p].l,key);//大了,去左子树找
    //去右边找的时候找的是在右子树中的排名,需要加上左子树和根的cnt
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r,key);
}

int get_key_by_rank(int p, int rank)   // 通过排名找数值
{
    if(!p) return INF;
    if(tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l,rank);
    //左边的个数>=rank,说明数值在左边
    if(tr[tr[p].l].size + tr[p].cnt >= rank)return tr[p].key;//左子树个数不够,加上当前cnt又多了,那就是当前数值
    return get_key_by_rank(tr[p].r,rank - tr[tr[p].l].size - tr[p].cnt); //去右子树中找数值,排名应该先减去左子树size+cnt
}


int get_prev(int p, int key)   // 找到严格小于key的最大数
{
    if(!p) return -INF;
    if(tr[p].key >= key) return get_prev(tr[p].l,key);//当前大于key,右子树不考虑
    return max(tr[p].key,get_prev(tr[p].r,key)); //当前key<key,不错,左子树都小于key所以不如key更好,所以考虑当前key和右子树

}
int get_next(int p, int key)    // 找到严格大于key的最小数
{
    if(!p) return INF;
    if(tr[p].key <= key)return get_next(tr[p].r,key); //当前key小于key,左子树不考虑
    return min(tr[p].key,get_next(tr[p].l,key)); //当前key>key,不错,右子树都大于key所以不如key更好,所以考虑当前key和左子树
}



int main(){
    build();
    int n;
    scanf("%d",&n);
    while(n --){
        int op,x;
        scanf("%d%d",&op,&x);
        if(op == 1) insert(root,x);
        else if (op == 2) remove(root,x);
        else if (op == 3) printf("%d\n",get_rank_by_key(root,x) - 1);//查排名,有-INF,排名要-1
        else if (op == 4) printf("%d\n",get_key_by_rank(root,x + 1));//查排名为x的数值,有-INF,内部排名为x + 1
        else if (op == 5) printf("%d\n",get_prev(root,x));
        else printf("%d\n",get_next(root,x));
    }
    return 0;

}
