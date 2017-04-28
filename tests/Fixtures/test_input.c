/*
 Multi line comment
 main function
 */
void main() {
    // MARK: - Declaration with Assignment
    int sum = 10 + 10;
    cout << sum << endl;

    // MARK: - Repeat
    cout << endl;
    repeat (3) {
        int sum = 25;
        cout << sum << endl;
    }

    // MARK: - Scoping
    cout << endl << sum << endl;

    // MARK: - While
    cout << endl;
    while (sum <= 100) {
        sum *= 2;
        cout << sum << endl;
    }

    // MARK: - DoWhile
    cout << endl;
    sum = 75;
    do {
        cout << sum << endl;
    } while (0);

    // MARK: - IfElse
    if (1 == 0 || 1) {
        cout << endl << 1 << endl;
    } else {
        cout << endl << 0 << endl;
    }

    if (0 != 0 && 1) {
        cout << endl << 1 << endl;
    } else {
        cout << endl << 0 << endl;
    }    
}
