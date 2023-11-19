//#define DEBUG

#ifdef DEBUG
//PREPEND BEGIN
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Data {
    int *entry;
    size_t row, col;
    size_t ref_cnt;

    Data(size_t row, size_t col) :
            row(row), col(col), ref_cnt(0) { entry = new int[row * col]{}; }

    ~Data() { delete[] entry; }
};

struct Matrix {
    Data *data;         // the ptr pointing to the entries
    size_t start;       // the starting index of ROI
    size_t row, col;    // the shape of ROI

    Matrix() :
            data(nullptr), start(0), row(0), col(0) {}

    ~Matrix() {
        if (!data)
            return;
        if (!--data->ref_cnt)
            delete data;
    }
};

void print_matrix(Matrix &mat) {
    for (size_t r = 0; r < mat.row; r++) {
        size_t head = mat.start + r * mat.data->col;
        for (size_t c = 0; c < mat.col; c++)
            cout << mat.data->entry[head + c] << ' ';
        cout << '\n';
    }
    cout << endl;
}
//PREPEND END
#endif

//TEMPLATE BEGIN
void unload_data(Matrix &mat) {
    if (mat.data) {
        if (--mat.data->ref_cnt == 0) {
            delete mat.data;
        }
    }
    mat.data = nullptr;
    mat.start = 0;
    mat.row = 0;
    mat.col = 0;
// Noted that `mat.data` could be `nullptr` here
}

void load_data(Matrix &mat, Data *data, size_t start, size_t row, size_t col) {
    unload_data(mat);
    mat.data = data;
    ++mat.data->ref_cnt;
    mat.start = start;
    mat.row = row;
    mat.col = col;
}

void shallow_copy(Matrix &dest, Matrix &src) {
    unload_data(dest);
    dest.data = src.data;
    ++src.data->ref_cnt;
    dest.start = src.start;
    dest.row = src.row;
    dest.col = src.col;
}

void deep_copy(Matrix &dest, Matrix &src) {
    unload_data(dest);
    dest.data = new Data(src.row, src.col);
    dest.start = 0;
    dest.row = src.row;
    dest.col = src.col;
    dest.data->ref_cnt = 1;

    for (size_t r = 0; r < dest.row; ++r) {
        size_t src_head = src.start + r * src.data->col;
        memcpy(&dest.data->entry[r * dest.col], &src.data->entry[src_head], sizeof(int) * src.col);
    }
}

bool equal_matrix(Matrix &a, Matrix &b) {
    if (&a == &b) {
        return true;
    }
    if (a.row != b.row or a.col != b.col) {
        return false;
    }

    for (size_t r = 0; r < a.row; ++r) {
        size_t a_head = a.start + r * a.data->col;
        size_t b_head = b.start + r * b.data->col;
        for (size_t c = 0; c < a.col; ++c) {
            if (a.data->entry[a_head + c] != b.data->entry[b_head + c]) {
                return false;
            }
        }
    }
    return true;
}

void add_matrix(Matrix &dest, Matrix &a, Matrix &b) {
    if (a.row != b.row or a.col != b.col) {
        return;
    }

    unload_data(dest);
    load_data(dest, new Data(a.row, a.col), 0, a.row, a.col);

    if (dest.data && dest.data->ref_cnt == 1 and
        dest.data->col >= a.col and dest.data->row >= a.row) {
        dest.start = 0;
    } else {
        unload_data(dest);
        load_data(dest, new Data(a.row, a.col), 0, a.row, a.col);
    }
    for (size_t r = 0; r < a.row; ++r) {
        size_t a_head = a.start + r * a.data->col;
        size_t b_head = b.start + r * b.data->col;
        size_t d_head = dest.start + r * dest.data->col;
        for (size_t c = 0; c < a.col; ++c) {
            dest.data->entry[d_head + c] = a.data->entry[a_head + c] + b.data->entry[b_head + c];
        }
    }
}

void minus_matrix(Matrix &dest, Matrix &a, Matrix &b) {
    if (a.row != b.row or a.col != b.col) {
        return;
    }

    unload_data(dest);
    load_data(dest, new Data(a.row, a.col), 0, a.row, a.col);

    if (dest.data && dest.data->ref_cnt == 1 &&
        dest.data->col >= a.col && dest.data->row >= a.row) {
        dest.start = 0;
    } else {
        unload_data(dest);
        load_data(dest, new Data(a.row, a.col), 0, a.row, a.col);
    }

    for (size_t r = 0; r < a.row; ++r) {
        size_t a_head = a.start + r * a.data->col;
        size_t b_head = b.start + r * b.data->col;
        size_t d_head = dest.start + r * dest.data->col;
        for (size_t c = 0; c < a.col; ++c) {
            dest.data->entry[d_head + c] = a.data->entry[a_head + c] - b.data->entry[b_head + c];
        }
    }
}

void multiply_matrix(Matrix &dest, Matrix &a, Matrix &b) {
    if (a.col != b.row) {
        return;
    }

    unload_data(dest);
    load_data(dest, new Data(a.row, b.col), 0, a.row, b.col);

    int *temp = new int[b.col];
    for (size_t r = 0; r < a.row; ++r) {
        size_t a_head = a.start + r * a.data->col;
        size_t d_head = dest.start + r * dest.data->col;

        memset(temp, 0, sizeof(int) * b.col);
        for (size_t ac = 0; ac < a.col; ++ac) {
            size_t b_head = b.start + ac * b.data->col;
            for (size_t bc = 0; bc < b.col; ++bc) {
                temp[bc] += a.data->entry[a_head + ac] * b.data->entry[b_head + bc];
            }
        }
        memcpy(&dest.data->entry[d_head], temp, sizeof(int) * b.col);
    }


    delete[] temp;
}
//TEMPLATE END

#ifdef DEBUG

//APPEND BEGIN
void test() {
    // Sample code on how to use your library
    Data *da = new Data(3, 2), *db = new Data(2, 3);
    for (size_t i = 0; i < 6; i++)
        da->entry[i] = db->entry[i] = i;

    Matrix a, b, c;
    load_data(a, da, 0, 3, 2);  // the ROI is the whole matrix
    load_data(b, db, 0, 2, 3);
    print_matrix(a);
    /*
        0 1
        2 3
        4 5
    */
    print_matrix(b);
    /*
        0 1 2
        3 4 5
    */

    multiply_matrix(c, a, b);
    print_matrix(c);
    /*
        3 4 5
        9 14 19
        15 24 33
    */

    Matrix d, e, f;
    shallow_copy(d, c); // d, c -> (the same) data
    deep_copy(e, c);    // e->data have the exactly same content with c->ROI(data) with e.data.shape = c.ROI.shape
    // but their addresses are different and ref_cnts possibly differ
    load_data(f, c.data, 1, 3, 2);
    print_matrix(f);
    /*
        4 5
        14 19
        24 33
    */
    add_matrix(b, a, f);   // notice that the original b.data->ref_cnt becomes 0 and should be deleted
    print_matrix(b);
    /*
        4 6
        16 22
        28 38
    */

    minus_matrix(b, b, a);   // notice that the original b.data->ref_cnt becomes 0 and should be deleted
    print_matrix(b);

    cout << a.data->ref_cnt << ' ' << b.data->ref_cnt << ' '
         << c.data->ref_cnt << ' ' << d.data->ref_cnt << ' '
         << e.data->ref_cnt << ' ' << f.data->ref_cnt << endl;
    /*
        1 1 3 3 1 3
    */
}

int main() {
    test();
    return 0;
}
//APPEND END
#endif
