# Manual test checklist

Compile:
```sh
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o recommender
```

1. Browse catalogue; verify all sample products are listed.
2. Select Books, budget Rs. 700 and rating 4.0; verify only matching products appear.
3. Set a very low budget; verify the no-match message.
4. View a valid product ID; verify details and session history.
5. View the same ID again; verify history does not duplicate it.
6. Enter an unknown product ID; verify Product not found.
7. Enter invalid menu, budget or rating input; verify validation prompt.
8. Select 0; verify clean exit.

These are suggested manual tests. Mark tests as passed only after running them in the target environment.
