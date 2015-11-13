#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class MatrixTerm{
public:
    friend class SparseMatrix;
    friend class SparsePoly2D;
private:
    int row, col;
    double value;
};



class SparseMatrix{
public:
    SparseMatrix(int r,int c,int t=1){
        smArray = new MatrixTerm[t];
        terms = t;
        smArray[0].row =0;
        smArray[0].col =0;
        smArray[0].value = 0;
    } /* r rows, c columns; t is the capacity*/
    SparseMatrix(){}
    SparseMatrix(const SparseMatrix &sm); //copy constructor

    SparseMatrix& operator=(const SparseMatrix& sm1); //assignment operator
    SparseMatrix Add(SparseMatrix &b);
    ~SparseMatrix(){
        delete [] smArray;
    }
protected:
    MatrixTerm *smArray; // array of terms
    int capacity; // size of smArray (pre-allocation)
    int rows, columns; // size of matrix
    int terms;          // number of non-zero terms
};

SparseMatrix::SparseMatrix(const SparseMatrix &sm){

    terms = sm.terms;
    capacity = sm.capacity;
    rows = sm.rows;
    columns = sm.columns;
    smArray = new MatrixTerm[terms];

    for(int i=0;i<terms;i++){
        smArray[i].col = sm.smArray[i].col;
        smArray[i].row = sm.smArray[i].row;
        smArray[i].value = sm.smArray[i].value;
    }
}

SparseMatrix SparseMatrix::Add(SparseMatrix &b){
    MatrixTerm * tempMt;
    int term_num=0;
    int i,j;
    double temp_value;
    int temp_row,temp_col;
    tempMt = new MatrixTerm[terms+b.terms];

    i=j=0;

    while(i < terms || j <b.terms){                         //select this and b for i and j
        if(smArray[i].row == b.smArray[j].row){
            if(smArray[i].col == b.smArray[j].col){
                temp_row = smArray[i].row;
                temp_col = smArray[i].col;
                temp_value = smArray[i].value + b.smArray[j].value;
                i++,j++;
            }else if(smArray[i].col > b.smArray[j].col){
                    temp_row = smArray[i].row;
                    temp_col = smArray[i].col;
                    temp_value = smArray[i].value;
                    i++;
                }else{
                    temp_row = b.smArray[j].value;
                    temp_col = b.smArray[j].value;
                    temp_value = b.smArray[j].value;
                    j++;
                }
        }
        else if(smArray[i].row > b.smArray[j].row){
                temp_row = smArray[i].row;
                temp_col = smArray[i].col;
                temp_value = smArray[i].value;
                i++;
            }else{
                temp_row = b.smArray[j].row;
                temp_col = b.smArray[j].col;
                temp_value = b.smArray[j].value;
                j++;
            }
        tempMt[term_num].row = temp_row;
        tempMt[term_num].col = temp_col;
        tempMt[term_num].value = temp_value;
        term_num++;


    }

    delete [] smArray;
    smArray = tempMt;
    terms = term_num;
    return *this;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& sm1){

    terms = sm1.terms;
    capacity = sm1.capacity;
    rows = sm1.rows;
    columns = sm1.columns;
    if(smArray !=NULL) delete [] smArray;
    smArray = new MatrixTerm[terms];

    for(int i=0;i<sm1.terms;i++){
        smArray[i].row = sm1.smArray[i].row;
        smArray[i].col = sm1.smArray[i].col;
        smArray[i].value = sm1.smArray[i].value;
    }
    return *this;
}


//繼承宣告要不要parent class的宣告
class SparsePoly2D : public SparseMatrix{

public:
    void SetTerms(const int *x_exp, const int *y_exp, const double *coef, int n);
//    SparsePoly2D Add(const SparsePoly2D &p);
    double Eval(double x, double y);
    void Print();
};

void SparsePoly2D::SetTerms(const int *x_exp, const int *y_exp, const double *coef, int n){
    terms = n;
    if(smArray != NULL){                //check if already allocated
        delete [] smArray;
    }
    smArray = new MatrixTerm[n];
    for(int i=0;i<n;i++){
        smArray[i].row = x_exp[i];
        smArray[i].col = y_exp[i];
        smArray[i].value = coef[i];
    }
    for(int i=0;i<n;i++){                           //sort x
        for(int j=0;j < n-i-1;j++){
            if(smArray[j].row < smArray[j+1].row ){
                swap(smArray[j].row,smArray[j+1].row);
                swap(smArray[j].col,smArray[j+1].col);
                swap(smArray[j].value,smArray[j+1].value);
            }
        }
    }
    for(int i=0;i<n;i++){                           //if x equal sort y
        for(int j=0;j< n-i-1;j++){
            if(smArray[j].row == smArray[j+1].row){
                if(smArray[j].col < smArray[j+1].col){
                    swap(smArray[j].col,smArray[j+1].col);
                    swap(smArray[j].value,smArray[j+1].value);
                }
            }
        }
    }
}



void SparsePoly2D::Print(){
    for(int i=0;i<terms;i++){
        cout << "<"<< smArray[i].row <<","<<smArray[i].col <<","
             << smArray[i].value <<">";
    }
    cout <<endl;
}

double SparsePoly2D::Eval(double x, double y){
    double result = 0;
    double exp_t;
    for(int i= 0;i<terms;i++){
        exp_t = 1;
        exp_t *= pow(x,smArray[i].row);
        exp_t *= pow(y,smArray[i].col);
        result += smArray[i].value * exp_t;



    }

    return result;
}
