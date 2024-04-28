#ifndef DATA_STRUCTURES1_PRODUCT_H
#define DATA_STRUCTURES1_PRODUCT_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char* name;
    double price;
    double total_price;
    int amount;
} product;

typedef struct {
    product* buffer;
    int amount;
} products;

typedef struct {
    char* name;
    int amount;
} order;

typedef struct {
    order* buffer;
    int amount;
} orders;

//создает продукт
product createProductNotCopy(char* name, double price, int amount);

//загрузить продукт из файла
product loadProduct(FILE*f);

//сохранить продукт в файл
void saveProduct(product p, FILE*f);

//удалить продукт из памяти
void deleteProduct(product* p);

//загрузить продукты из файла
products loadProducts(FILE*f);

//сохранить продукты в файл
void saveProducts(products ps, FILE*f);

//удалить продукты из памяти
void deleteProducts(products* ps);

//загрузить заказ из файла
order loadOrder(FILE*f);

//сохранить заказ в файл
void saveOrder(order o, FILE*f);

//удалить заказ
void deleteOrder(order* o);

//загрузить заказы из файла
orders loadOrders(FILE*f);

//сохранить заказы в файл
void saveOrders(orders os, FILE* f);

//удалить заказы
void deleteOrders(orders* os);

//выполняет заказы
void fulfillOrders(products* ps, orders os);

//сравнение заказов
bool cmpProducts(product p1, product p2);

//выводит на экран продукт
void printProduct(product p);

//выводит на экран продукты
void printProducts(products ps);

#endif //DATA_STRUCTURES1_PRODUCT_H
