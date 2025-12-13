#include <iostream>
using namespace std;

/* --------------------------
   Booking Structure
   -------------------------- */
struct Booking {
    int userId;
};

int main() {
    cout << "=== Gaming & Entertainment Booking System ===\n";

    // Store single booking (simple replacement for AVL Tree)
    Booking userBooking;
    userBooking.userId = 101;

    // Seat availability per zone (simple array instead of Segment Tree)
    int seatBlocks[4] = {5, 3, 8, 6}; // zones 1 to 4

    int zoneL = 1, zoneR = 3;
    int priceL = 200, priceR = 500; // kept for logic clarity

    // Check availability
    int available = 0;
    for (int i = zoneL - 1; i < zoneR; i++) {
        available += seatBlocks[i];
    }

    // Allocate seat
    if (available > 0) {
        cout << "Seat allocated for User ID: " << userBooking.userId << endl;
        cout << "Available seats: " << available << endl;
        cout << "Entertainment booking confirmed!" << endl;
    } else {
        cout << "No seats available." << endl;
    }

    return 0;
}
