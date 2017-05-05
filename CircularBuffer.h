// functions to add and remove values to the circular buffer
// the buffer assumes all values are positive. We use -1 to indicate producer
// has added all values.
void initBuffer();
void addToBuffer(int val);
int removeFromBuffer();
