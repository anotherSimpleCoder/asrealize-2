class asrVector{
private:
	int x;
	int y;

public:
	asrVector(int pX, int pY);

	//getters
	int getPosition(int component);

	//setters
	void setPosition(int component, int value);

};
