#include "product.h"
#include <malloc.h>
#include <stdbool.h>
#include <math.h>
#include "../string/tasks/string.h"

double loadDouble(FILE*f) {
    double x;
    fread(&x, sizeof (double), 1, f);
    return x;
}

int loadInt(FILE*f) {
    int x;
    fread(&x, sizeof (int), 1, f);
    return x;
}

void saveDouble(double x, FILE*f) {
    fwrite(&x, sizeof (double), 1, f);
}

void saveInt(int x, FILE*f) {
    fwrite(&x, sizeof (int), 1, f);
}

product createProductNotCopy(char* name, double price, int amount) {
    double total_price = price*amount;
    product p;
    p.name = name;
    p.price = price;
    p.total_price = total_price;
    p.amount = amount;
    return p;
}

product loadProduct(FILE*f) {
    product p;
    p.name = loadStr(f);
    p.price = loadDouble(f);
    p.total_price = loadDouble(f);
    p.amount = loadInt(f);
    return p;
}

void saveProduct(product p, FILE*f) {
    saveStrInBin(p.name, f);
    saveDouble(p.price, f);
    saveDouble(p.total_price, f);
    saveInt(p.amount, f);
}

void deleteProduct(product* p) {
    free(p->name);
    p->name = NULL;
    p->price = 0;
    p->total_price = 0;
    p->amount = 0;
}

products loadProducts(FILE*f) {
    products ps;
    fread(&ps.amount, sizeof (int), 1, f);
    ps.buffer = malloc(ps.amount*sizeof(product));
    for (int i = 0; i < ps.amount; ++i) {
        ps.buffer[i] = loadProduct(f);
    }
    return ps;
}

void saveProducts(products ps, FILE*f) {
    fwrite(&ps.amount, sizeof (int), 1, f);
    for (int i = 0; i < ps.amount; ++i) {
        saveProduct(ps.buffer[i], f);
    }
}

void deleteProducts(products* ps) {
    for (int i = 0; i < ps->amount; ++i) {
        deleteProduct(&ps->buffer[i]);
    }
    free(ps->buffer);
    ps->buffer = NULL;
    ps->amount = 0;
}

order loadOrder(FILE*f) {
    order o;
    o.name = loadStr(f);
    o.amount = loadInt(f);
    return o;
}

void saveOrder(order o, FILE*f) {
    saveStrInBin(o.name, f);
    saveInt(o.amount,f);
}

void deleteOrder(order* o) {
    free(o->name);
    o->name = NULL;
    o->amount = 0;
}

orders loadOrders(FILE*f) {
    orders os;
    fread(&os.amount, sizeof (int), 1, f);
    os.buffer = malloc(os.amount*sizeof(order));
    for (int i = 0; i < os.amount; ++i) {
        os.buffer[i] = loadOrder(f);
    }
    return os;
}

void saveOrders(orders os, FILE* f) {
    fwrite(&os.amount, sizeof (int), 1, f);
    for (int i = 0; i < os.amount; ++i) {
        saveOrder(os.buffer[i], f);
    }
}

void deleteOrders(orders* os) {
    for (int i = 0; i < os->amount; ++i) {
        deleteOrder(&os->buffer[i]);
    }
    free(os->buffer);
    os->buffer = NULL;
    os->amount = 0;
}

void fulfillOrders(products* ps, orders os) {
    for (int i = 0; i < os.amount; ++i) {
        for (int j = 0; j < ps->amount; ++j) {
            if (!strcmp(os.buffer[i].name, ps->buffer[j].name)) {
                ps->buffer[j].amount -= os.buffer[i].amount;
                if (ps->buffer[j].amount<=0) {
                    deleteProduct(&ps->buffer[j]);
                    ps->buffer[j--] = ps->buffer[--ps->amount];
                } else
                    ps->buffer[j].total_price = ps->buffer[j].price*
                            ps->buffer[j].amount;
                break;
            }
        }
    }
}

bool cmpProducts(product p1, product p2) {
    return p1.amount==p2.amount && p1.total_price==p2.total_price &&
        p1.price==p2.price && !(strcmp(p1.name, p2.name));
}

void printProduct(product p) {
    printf("%s %lf %lf %d\n", p.name, p.price, p.total_price, p.amount);
}

void printProducts(products ps) {
    for (int i = 0; i < ps.amount; ++i) {
        printProduct(ps.buffer[i]);
    }
    putchar('\n');
}