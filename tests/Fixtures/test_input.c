/*
 Multi line comment
 main function
 */
void main() {
    // MARK: - Declaration with Assignment
    int sum = 10 + 10;
    int x = 250;
    cout << sum << endl;
    cout << x << endl;

    // MARK: - Plus, Minus, Divide, Multiply
    cout << endl;
    cout << 20 + 5 << endl;
    cout << 30 - 5 << endl;
    cout << 100 / 4 << endl;
    cout << 5 * 5 << endl;
    cout << endl;

    // MARK: - Increment
    x++;
    cout << x << endl;

    // MARK: - Decrement
    x--;
    cout << x << endl;

    // MARK: - Modulus
    cout << 7 % 5 << endl;

    // MARK: - Not
    cout << !1 << endl;

    // MARK: - Negative
    cout << -5 + 5 << endl;

    // MARK: - Repeat
    cout << endl;
    repeat (1) {
        int sum = 25;
        x = 300;
        cout << sum << x << endl;
    }

    // MARK: - Scoping
    cout << endl << sum << x << endl;

    // MARK: - While
    cout << endl;
    while (sum <= 100) {
        sum += 25;
        cout << sum << endl;
    }

    // MARK: - DoWhile
    cout << endl;
    sum = 75;
    do {
        cout << sum << endl;
    } while (0);

    // MARK: - IfElse TRUE
    if (1 == 0 || 1) {
        cout << endl << 1 << endl;
    } else {
        cout << endl << 0 << endl;
    }

    // MARK: - IfElse FALSE
    if (0 != 0 && 1) {
        cout << endl << 1 << endl;
    } else {
        cout << endl << 0 << endl;
    }    
}
