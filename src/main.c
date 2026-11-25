#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PRODUCTS 30
#define MAX_HISTORY 50
#define NAME_LEN 64
#define CAT_LEN 32
typedef struct { int id; char name[NAME_LEN]; char category[CAT_LEN]; double price, rating; int popularity; } Product;
typedef struct { char category[CAT_LEN]; double budget, min_rating; int viewed[MAX_HISTORY], viewed_count; } User;
static Product products[] = {
{101,"Wireless Headphones","Electronics",2499,4.5,95},{102,"Bluetooth Speaker","Electronics",1799,4.2,82},{103,"Smart Watch","Electronics",3299,4.4,88},{104,"USB-C Fast Charger","Electronics",699,4.1,74},
{201,"Running Shoes","Fashion",2199,4.3,91},{202,"Cotton T-Shirt","Fashion",599,4.0,78},{203,"Everyday Backpack","Fashion",1299,4.2,80},{204,"Classic Wrist Watch","Fashion",1899,4.6,69},
{301,"Programming in C","Books",499,4.7,96},{302,"Data Structures Handbook","Books",649,4.5,89},{303,"Fiction Collection","Books",399,4.1,67},
{401,"Desk Lamp","Home",899,4.2,72},{402,"Water Bottle","Home",349,4.0,85},{403,"Study Chair","Home",4599,4.4,63}};
#define PRODUCT_COUNT ((int)(sizeof(products)/sizeof(products[0])))
static void read_line(const char *p,char *b,size_t n){printf("%s",p);if(!fgets(b,(int)n,stdin)){b[0]=0;return;}b[strcspn(b,"\n")]=0;}
static int read_int(const char *p,int lo,int hi){char s[80],x;int v;for(;;){read_line(p,s,sizeof s);if(sscanf(s,"%d %c",&v,&x)==1&&v>=lo&&v<=hi)return v;printf("Enter a number from %d to %d.\n",lo,hi);}}
static double read_double(const char *p,double lo,double hi){char s[80],x;double v;for(;;){read_line(p,s,sizeof s);if(sscanf(s,"%lf %c",&v,&x)==1&&v>=lo&&v<=hi)return v;printf("Enter a value from %.2f to %.2f.\n",lo,hi);}}
static int same(const char *a,const char *b){while(*a&&*b){if(tolower((unsigned char)*a)!=tolower((unsigned char)*b))return 0;a++;b++;}return *a==0&&*b==0;}
static int viewed(const User *u,int id){int i;for(i=0;i<u->viewed_count;i++)if(u->viewed[i]==id)return 1;return 0;}
static void remember(User *u,int id){if(!viewed(u,id)&&u->viewed_count<MAX_HISTORY)u->viewed[u->viewed_count++]=id;}
static int find_index(int id){int i;for(i=0;i<PRODUCT_COUNT;i++)if(products[i].id==id)return i;return -1;}
static void print_product(const Product *p){printf("%-4d %-27s %-13s Rs.%-9.2f %.1f/5  %d\n",p->id,p->name,p->category,p->price,p->rating,p->popularity);}
static void catalogue(void){int i;puts("\nID   Product                     Category      Price       Rating Popularity");for(i=0;i<PRODUCT_COUNT;i++)print_product(&products[i]);}
static double score(const Product *p,const User *u){double s=0;if(same(p->category,u->category))s+=50;if(p->price<=u->budget)s+=20;s+=p->rating*5+p->popularity*0.1;if(viewed(u,p->id))s-=100;return s;}
static void recommend(User *u){int idx[MAX_PRODUCTS],n=0,i,j,t;double sc[MAX_PRODUCTS],d;for(i=0;i<PRODUCT_COUNT;i++)if(products[i].price<=u->budget&&products[i].rating>=u->min_rating&&!viewed(u,products[i].id)){idx[n]=i;sc[n]=score(&products[i],u);n++;}for(i=0;i<n-1;i++)for(j=i+1;j<n;j++)if(sc[j]>sc[i]){d=sc[i];sc[i]=sc[j];sc[j]=d;t=idx[i];idx[i]=idx[j];idx[j]=t;}printf("\nTop recommendations for %s (budget Rs. %.2f):\n",u->category,u->budget);if(!n){puts("No products match. Adjust your filters.");return;}puts("ID   Product                     Category      Price       Rating Popularity");for(i=0;i<n&&i<5;i++)print_product(&products[idx[i]]);puts("Ranking uses category match, budget, rating and popularity.");}
static void preferences(User *u){char c[CAT_LEN];puts("Categories: Electronics, Fashion, Books, Home");read_line("Preferred category: ",c,sizeof c);if(!c[0]){puts("Category cannot be empty.");return;}strcpy(u->category,c);u->budget=read_double("Maximum budget (Rs. 1-100000): ",1,100000);u->min_rating=read_double("Minimum rating (0-5): ",0,5);puts("Preferences updated.");}
static void view_product(User *u){int id=read_int("Product ID: ",1,999999),k=find_index(id);if(k<0){puts("Product not found.");return;}print_product(&products[k]);remember(u,id);puts("Added to viewed history.");}
int main(void){User user={"Electronics",3000,0,{0},0};int c,i,k;puts("E-commerce Product Recommendation System | C");for(;;){puts("\n1. Browse catalogue\n2. Set preferences\n3. Get recommendations\n4. View product\n5. View session history\n0. Exit");c=read_int("Choice: ",0,5);switch(c){case 1:catalogue();break;case 2:preferences(&user);break;case 3:recommend(&user);break;case 4:view_product(&user);break;case 5:if(!user.viewed_count)puts("No products viewed.");else for(i=0;i<user.viewed_count;i++){k=find_index(user.viewed[i]);if(k>=0)print_product(&products[k]);}break;case 0:puts("Goodbye.");return 0;}}}
