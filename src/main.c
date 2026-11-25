#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PRODUCTS 30
#define MAX_HISTORY 50
#define NAME_LEN 64
#define CAT_LEN 32

typedef struct {
    int id;
    char name[NAME_LEN];
    char category[CAT_LEN];
    double price, rating;
    int popularity;
} Product;

typedef struct {
    char category[CAT_LEN];
    double budget, min_rating;
    int viewed[MAX_HISTORY], viewed_count;
} User;

static Product products[] = {
    {101,"Wireless Headphones","Electronics",2499,4.5,95},
    {102,"Bluetooth Speaker","Electronics",1799,4.2,82},
    {103,"Smart Watch","Electronics",3299,4.4,88},
    {104,"USB-C Fast Charger","Electronics",699,4.1,74},
    {201,"Running Shoes","Fashion",2199,4.3,91},
    {202,"Cotton T-Shirt","Fashion",599,4.0,78},
    {203,"Everyday Backpack","Fashion",1299,4.2,80},
    {204,"Classic Wrist Watch","Fashion",1899,4.6,69},
    {301,"Programming in C","Books",499,4.7,96},
    {302,"Data Structures Handbook","Books",649,4.5,89},
    {303,"Fiction Collection","Books",399,4.1,67},
    {401,"Desk Lamp","Home",899,4.2,72},
    {402,"Water Bottle","Home",349,4.0,85},
    {403,"Study Chair","Home",4599,4.4,63}
};
#define PRODUCT_COUNT ((int)(sizeof(products) / sizeof(products[0])))

static void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, (int)size, stdin)) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

static int read_int(const char *prompt, int low, int high) {
    char line[80], extra;
    int value;
    for (;;) {
        read_line(prompt, line, sizeof line);
        if (sscanf(line, "%d %c", &value, &extra) == 1 &&
            value >= low && value <= high) return value;
        printf("Enter a number from %d to %d.\n", low, high);
    }
}

static double read_double(const char *prompt, double low, double high) {
    char line[80], extra;
    double value;
    for (;;) {
        read_line(prompt, line, sizeof line);
        if (sscanf(line, "%lf %c", &value, &extra) == 1 &&
            value >= low && value <= high) return value;
        printf("Enter a value from %.2f to %.2f.\n", low, high);
    }
}

static int same_category(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        ++a;
        ++b;
    }
    return *a == '\0' && *b == '\0';
}

static int has_viewed(const User *user, int id) {
    int i;
    for (i = 0; i < user->viewed_count; ++i)
        if (user->viewed[i] == id) return 1;
    return 0;
}

static void remember_view(User *user, int id) {
    if (!has_viewed(user, id) && user->viewed_count < MAX_HISTORY)
        user->viewed[user->viewed_count++] = id;
}

static int find_product_index(int id) {
    int i;
    for (i = 0; i < PRODUCT_COUNT; ++i)
        if (products[i].id == id) return i;
    return -1;
}

static void print_product(const Product *product) {
    printf("%-4d %-27s %-13s Rs.%-9.2f %.1f/5  %d\n",
           product->id, product->name, product->category,
           product->price, product->rating, product->popularity);
}

/* Transparent rule-based ranking score; higher scores rank first. */
static double recommendation_score(const Product *product, const User *user) {
    double score = 0.0;
    if (same_category(product->category, user->category)) score += 50.0;
    score += 20.0 * (user->budget - product->price) / user->budget;
    score += product->rating * 5.0;
    score += product->popularity * 0.10;
    if (has_viewed(user, product->id)) score -= 100.0;
    return score;
}

static void show_catalogue(void) {
    int i;
    puts("\nID   Product                     Category      Price       Rating Popularity");
    for (i = 0; i < PRODUCT_COUNT; ++i) print_product(&products[i]);
}

static void show_recommendations(User *user) {
    int indices[MAX_PRODUCTS], count = 0, i, j, temp_index;
    double scores[MAX_PRODUCTS], temp_score;

    for (i = 0; i < PRODUCT_COUNT; ++i) {
        if (products[i].price <= user->budget &&
            products[i].rating >= user->min_rating) {
            indices[count] = i;
            scores[count] = recommendation_score(&products[i], user);
            ++count;
        }
    }

    for (i = 0; i < count - 1; ++i) {
        for (j = i + 1; j < count; ++j) {
            if (scores[j] > scores[i]) {
                temp_score = scores[i]; scores[i] = scores[j]; scores[j] = temp_score;
                temp_index = indices[i]; indices[i] = indices[j]; indices[j] = temp_index;
            }
        }
    }

    printf("\nTop recommendations for %s (budget Rs. %.2f):\n",
           user->category, user->budget);
    if (count == 0) {
        puts("No products match. Adjust your filters.");
        return;
    }
    puts("ID   Product                     Category      Price       Rating Popularity");
    for (i = 0; i < count && i < 5; ++i) print_product(&products[indices[i]]);
    puts("Viewed products receive a ranking penalty; the catalogue is sample data.");
}

static void set_preferences(User *user) {
    char category[CAT_LEN];
    puts("Categories: Electronics, Fashion, Books, Home");
    read_line("Preferred category: ", category, sizeof category);
    if (category[0] == '\0') {
        puts("Category cannot be empty.");
        return;
    }
    strcpy(user->category, category);
    user->budget = read_double("Maximum budget (Rs. 1-100000): ", 1, 100000);
    user->min_rating = read_double("Minimum rating (0-5): ", 0, 5);
    puts("Preferences updated for this session.");
}

static void view_product(User *user) {
    int id = read_int("Product ID: ", 1, 999999);
    int index = find_product_index(id);
    if (index < 0) {
        puts("Product not found.");
        return;
    }
    print_product(&products[index]);
    remember_view(user, id);
    puts("Added to viewed history.");
}

static void show_menu(void) {
    puts("\n========== E-COMMERCE PRODUCT RECOMMENDER ==========");
    puts("1. Browse catalogue");
    puts("2. Set recommendation preferences");
    puts("3. Get recommendations");
    puts("4. View a product");
    puts("5. Show viewed product history");
    puts("0. Exit");
}

int main(void) {
    User user = {"Electronics", 3000.0, 0.0, {0}, 0};
    int choice, i, index;

    puts("E-commerce Product Recommendation System | C");
    for (;;) {
        show_menu();
        choice = read_int("Choose an option: ", 0, 5);
        switch (choice) {
            case 1:
                show_catalogue();
                break;
            case 2:
                set_preferences(&user);
                break;
            case 3:
                show_recommendations(&user);
                break;
            case 4:
                view_product(&user);
                break;
            case 5:
                if (user.viewed_count == 0) puts("No products viewed in this session.");
                else {
                    puts("\nViewed products:");
                    for (i = 0; i < user.viewed_count; ++i) {
                        index = find_product_index(user.viewed[i]);
                        if (index >= 0) print_product(&products[index]);
                    }
                }
                break;
            case 0:
                puts("Thank you for using the recommender.");
                return 0;
        }
    }
}
