
#include<iostream>

using namespace std;

class TridiagonalMatrix{
public:
    TridiagonalMatrix(int n){
        this->n = n;
        list = new int[3*n-2];
    }

    ~TridiagonalMatrix(){delete []list;}

    int getDimision(){
        return n;
    }
    TridiagonalMatrix& store(const int &x, int i, int j){
        if(i<1 || i>n || j<1 || j>n){
            printf("Error:Invalid position!\n");
        } else if((i-j>1 || j-i>1) && x!=0){
            printf("The element in (%d,%d) must be 0!\n", i, j);
        } else if(i-j<=1 || j-i<=1){
            list[2*j+i-3] = x;
            printf("Put element %d in array at array[2*%d+%d-3]\n", x, j, i );
        }
    }

    int retrieve(int i, int j){
        if(i<1 || i>n || j<1 || j>n){
            printf("Error:Invalid position!\n");
        } else if(i-j>1 || j-i>1){
            return 0;
        } else {
            return list[2*j+i-3];
        }
    }
private:
    int n = 0;
    int* list;
};

class LowerMatrix{
public:
    LowerMatrix(int n){
        this->n = n;
        list = new int[n*(n+1)/2];
    }

    LowerMatrix& store(const int &x, int i, int j){
        if((i<1 || i>n || j<1 || j>n)){
            printf("Error:Invalid position!\n");
        } else if(i<j && x!=0){
            printf("The element in (%d,%d) must be 0!\n", i, j);
        } else if(i>=j){
            list[(i-1)*i/2+j-1] = x;
            printf("Put element %d in array at array[(%d-1)*%d/2+%d-1]\n" , x, i, i, j);
        }
    };

    int retrieve(int i, int j){
        if((i<1 || i>n || j<1 || j>n)){
            printf("Error:Invalid position!\n");
        } else if(i<j){
            return 0;
        } else if(i>=j){
            return list[(i-1)*i/2+j-1];
        }
    }

private:
    int n = 0;
    int* list;
};

class Term{
public:
    Term(int value=0, int row=0, int col=0){
        this->value = value;
        this->row = row;
        this->col = col;
    }
    int value = 0;
    int row = 0;
    int col = 0;

    //Setters and Getters（神经病的封装）
//    int getValue(){return value;}
//    int getRow(){return row;}
//    int getCol(){return col;}
//    void setValue(int value){this->value = value;}
//    void setRow(int row){this->row = row;}
//    void setCol(int Col){this->col = col;}
private:

};

class SparseMatrix{
public:
    SparseMatrix(int max){
        if(max < 1){
            cout << "Bad Initializers\n" << endl;
        } else {
            maxTerms = max;
            rows = 0;
            cols = 0;
            array = new Term[max];
        }
    }
    ~SparseMatrix(){delete []array;}

    void init(){
        /*
         * 矩阵初始化方法。
         * 提示用户输入矩阵的行、列、非零元素数。并提示用户输入数个非零元素。
         * 用户可以按任意顺序输入，该方法会自动为用户输入的数据进行排序，从而达到行映射的要求排列。
         */
        cout << "Enter the number of rows, columns, and terms(Split them using one space)\n" << endl;
        cin >> rows >> cols >> terms;
        if(terms > maxTerms){
            printf("Int \"terms\" is to big!(maxTerms is %d)\n", maxTerms);
        } else {
//            Term* array = new Term[terms];
            for(int i=0; i<terms; i++){
                cout << "Enter row, column, and value of term" << (i+1) << " (Split them using one space)" << endl;
                cin >> array[i].row >> array[i].col >> array[i].value;
                if(array[i].row > rows || array[i].col > cols || array[i].row < 1 || array[i].col < 1){
                    i--;
                    printf("Invalid term!Please try again! (Max row is %d and max col is %d!)\n", rows, cols);
                }
            }
            //基数排序，使输入的数据按照行映射排列
            int maxDim = rows>cols ? rows:cols;
            int* rowSize = new int[maxDim+1];
            for(int i=0; i<maxDim+1; i++){
                rowSize[i] = 0;
            }
            Term** sortBase = new Term*[maxDim+1];
            for(int i=0; i<maxDim+1; i++){
                sortBase[i] = new Term[terms];
            }
            for(int i=0; i<terms; i++){
                sortBase[array[i].col][rowSize[array[i].col]] = array[i];
                rowSize[array[i].col]++;
            }
            int k = 0;){
                if(array[ct].row == another.array[ca].row){
            for(int i=1; i<maxDim+1; i++){
                for(int j=0; j<rowSize[i]; j++){
                    array[k] = sortBase[i][j];
                    k++;
                }
            }
            for(int i=0; i<maxDim+1; i++){
                rowSize[i] = 0;
            }
            for(int i=0; i<terms; i++){
                sortBase[array[i].row][rowSize[array[i].row]] = array[i];
                rowSize[array[i].row]++;
            }
            k = 0;
            for(int i=1; i<maxDim+1; i++){
                for(int j=0; j<rowSize[i]; j++){
                    array[k] = sortBase[i][j];
                    k++;
                }
            }
        }
    }

    void init_by_default(){
        /*
         * 使用6个默认非零元素初始化一个99*99的稀疏矩阵。
         */
        cols = 99;
        rows = 99;
        terms = 6;
        Term *t1= new Term(1,23,44);
        Term *t2 = new Term(1,33,24);
        Term *t3 = new Term(1,54,13);
        Term *t4 = new Term(1,65,2);
        Term *t5 = new Term(1,73,88);
        Term *t6 = new Term(1,86,7);
        array[0] = *t1;
        array[1] = *t2;
        array[2] = *t3;
        array[3] = *t4;
        array[4] = *t5;
        array[5] = *t6;

    }

    void output(){
        //输出矩阵信息
        cout << "#Matrix Info : " << endl;
        printf("rows = %d, cols = %d, nonzero terms = %d\n", rows, cols, terms);
        cout << "#Terms Info : " << endl;
        for(int i=0; i<terms; i++){
            printf("Matrix(%d, %d) = %d\n", array[i].row, array[i].col, array[i].value);
        }
    }

    void append(const Term& t){
        if(terms >= maxTerms){
            cout << "Too many terms!" << endl;
        } else {
            array[terms] = t;
            terms ++;
        }
    }

    SparseMatrix* transpose(){
        /*
         * 矩阵转置的方法。返回转置之后的矩阵。
         */
        SparseMatrix* newMatrix = new SparseMatrix(maxTerms);
        newMatrix->cols = rows;
        newMatrix->rows = cols;
        newMatrix->terms = terms;
        int *colSize, *rowNext;
        colSize = new int[cols+1];
        rowNext = new int[cols+1];
        for(int i=1; i<=cols; i++){
            colSize[i] = 0;
        }
        for(int i=0; i<terms; i++){
            colSize[array[i].col] ++;
        }
        rowNext[1] = 0;
        for(int i=2; i<=cols; i++){
            rowNext[i] = rowNext[i-1] + colSize[i-1];
        }
        for(int i=0; i<terms; i++){
            int j = rowNext[array[i].col]++;
            newMatrix->array[j].row = array[i].col;
            newMatrix->array[j].col = array[i].row;
            newMatrix->array[j].value = array[i].value;
        }

        return newMatrix;
    }

    SparseMatrix* add(SparseMatrix &another){
        /*
         * 矩阵加法，将原矩阵和传入的another矩阵相加，返回相加后得到的新矩阵。
         * 优化：完成对应项相加后会自动去除0项。
         */
        SparseMatrix* newMatrix = new SparseMatrix(maxTerms+another.maxTerms);
        if(rows != another.rows || cols != another.cols){
            cout << " Matrix size mismatched! Can't add!" << endl;
        } else {
            newMatrix->rows = rows;
            newMatrix->cols = cols;
            newMatrix->terms = 0;
            int ct = 0;
            int ca = 0;
            while(ct < terms && ca < another.terms){
                if(array[ct].row == another.array[ca].row){
                    if(array[ct].col == another.array[ca].col){
                        Term *t= new Term(array[ct].value + another.array[ca].value,
                                          array[ct].row, array[ct].col);
                        newMatrix->append(*t);
                        ct++;
                        ca++;
//                        newMatrix->terms --;
                    } else {
                        int nCol = array[ct].col < another.array[ca].col ? array[ct].col : another.array[ca].col;
                        int nRow = array[ct].col < another.array[ca].col ? array[ct].row : another.array[ca].row;
                        int nValue = array[ct].col < another.array[ca].col ? array[ct].value : another.array[ca].value;
                        Term *t = new Term(nValue, nRow, nCol);
                        newMatrix->append(*t);
                        array[ct].col < another.array[ca].col ? ct++ : ca++;
                    }

                } else {
                    int nCol = array[ct].row < another.array[ca].row ? array[ct].col : another.array[ca].col;
                    int nRow = array[ct].row < another.array[ca].row ? array[ct].row : another.array[ca].row;
                    int nValue = array[ct].row < another.array[ca].row ? array[ct].value : another.array[ca].value;
                    Term *t = new Term(nValue, nRow, nCol);
                    newMatrix->append(*t);
                    array[ct].row < another.array[ca].row ? ct++ : ca++;
                }
            }
            while(ct<terms){
                Term *t = new Term(array[ct].value, array[ct].row,array[ct].col);
                newMatrix->append(*t);
                ct++;
            }
            while(ca<another.terms){
                Term *t = new Term(another.array[ca].value, another.array[ca].row, another.array[ca].col);
                newMatrix->append(*t);
                ca++;
            }
            for(int i=0; i<newMatrix->terms; i++){
                if(newMatrix->array[i].value == 0){
                    for(int j=i; j<newMatrix->terms-1; j++){
                        newMatrix->array[j] = newMatrix->array[j+1];
                    }
//                    newMatrix->array[newMatrix->terms-1];
                    newMatrix->terms--;
                    i--;
                }
            }
        }
        return newMatrix;
    }

private:
    int rows = 0;
    int cols = 0;
    int terms = 0;
    Term* array;
    int maxTerms = 0;
};

int main(){
    //测试三对角矩阵
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------Testing TridiagonalMatrix--------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    TridiagonalMatrix* tri = new TridiagonalMatrix(5);
    tri->store(3, 1, 5);//在应该是0的地方存储非零元素
    tri->store(7, -3, 3);//标号不合法
    tri->store(2, 3, 4);//正常存储
    tri->store(5, 3, 3);
    cout << tri->retrieve(3,4) << endl;//获取（3,4）处的元素

    //测试下三角矩阵
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------Testing LowerMatrix--------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    LowerMatrix* low = new LowerMatrix(5);
    low->store(3, 4, 5);//在应该是0的地方存储非零元素
    low->store(5, -2, 3);//标号不合法
    low->store(9, 3, 3);//正常存储
    low->store(5, 5, 3);
    cout << low->retrieve(3,3) << endl;//获取（3,3）处的元素

    //测试稀疏矩阵
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------Testing SparseMatrix--------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    SparseMatrix* spa = new SparseMatrix(100);
    spa->init();
    spa->output();

    cout << "--------------------------------After transposing--------------------------------" << endl;
    SparseMatrix* transposedMatrix = spa->transpose();
    transposedMatrix->output();

    cout << "--------------------------------After adding another matrix--------------------------------" <<endl;
    SparseMatrix *another = new SparseMatrix(100);
    another->init_by_default();//调用自动初始化方法。
    spa = spa->add(*another);
    spa->output();
    return 0;
}
