# E-commerce Product Recommendation System (C)

A menu-driven C-language academic project demonstrating a simple rule-based product recommender.

## Features
- Browse a sample product catalogue across Electronics, Fashion, Books and Home.
- Set category, maximum budget and minimum rating preferences.
- Display up to five eligible recommendations, ranked by a weighted score.
- View products and maintain a session-only viewed-product history.
- Validate numeric menu and preference inputs.

## Recommendation method
Eligible products satisfy the selected budget and minimum rating. They are ranked using:
- +50 for preferred-category match
- +20 for being within budget
- +5 multiplied by product rating
- +0.10 multiplied by popularity
- -100 for products already viewed in the current session

This is a transparent rule-based demonstration, not machine learning or a live commercial recommendation service.

## Data structures and algorithms
The program uses C structures for Product and User, fixed-size arrays for the catalogue and view history, linear search to locate products by ID, and a nested-loop comparison sort to rank eligible items.

## Build and run
Requires GCC or another C99-compatible compiler.

```sh
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o recommender
./recommender
```

## Structure
```
E-Commerce-Product-Recommendation-System/
├── README.md
├── src/
│   └── main.c
└── docs/
    └── TESTING.md
```

## Scope and limitations
The catalogue and ratings are illustrative hard-coded sample data. User preferences and viewed history are held in memory only and reset when the program exits. There is no database, login, network integration, payment or inventory service, or web interface.
