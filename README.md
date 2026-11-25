# E-commerce Product Recommendation System (C)

A menu-driven C-language academic project demonstrating a simple rule-based product recommender.

## Team Members

| S. No. | Name | Roll Number |
|---:|---|---|
| 1 | Abhishek Samanta | 02896303125 |
| 2 | Aishwarya Singh | 00996303125 |
| 3 | Khushi Joshi | 03596303125 |

## Features
- Browse a sample catalogue of 14 products across Electronics, Fashion, Books and Home.
- Set a preferred category, maximum budget and minimum rating.
- Display up to five eligible recommendations, ranked by a weighted score.
- View product details and maintain a session-only viewed-product history.
- Validate numeric menu and preference inputs.

## Recommendation method
Products are eligible when they are within the selected budget and meet the minimum rating. Eligible products are sorted by this score (higher is better):
- +50 points for preferred-category match
- Up to +20 points based on remaining budget: 20 x (budget - price) / budget
- +5 multiplied by product rating
- +0.10 multiplied by popularity
- -100 points for a product already viewed in the current session

This is a transparent rule-based educational recommender, not machine learning or a live commercial recommendation service.

## Data structures and algorithms
The program uses C structures for Product and User, fixed-size arrays for the catalogue and view history, linear search to locate products by ID, and a nested-loop comparison sort to rank eligible products.

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
The catalogue, ratings and popularity values are illustrative hard-coded sample data. User preferences and viewed history are held in memory only and reset when the program exits. There is no database, login, network integration, payment or inventory service, or web interface.
