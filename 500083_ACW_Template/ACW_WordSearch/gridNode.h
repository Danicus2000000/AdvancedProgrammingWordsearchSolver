#pragma once
class gridNode
{
private:
    gridNode* up, * down, * left, * right, * upRight, * upLeft, * downLeft, * downRight;
    char letter;
public:
    explicit gridNode(const char letterToAdd);
    gridNode(const gridNode& o) : up(nullptr), down(nullptr), left(nullptr), right(nullptr), upRight(nullptr), upLeft(nullptr), downLeft(nullptr), downRight(nullptr), letter(o.letter) //copy constructor for gridNode to satisfy Parasoft issues
    {  

    }
    gridNode &operator=(const gridNode& o)
    {
        if(&o!=this)
        {
            up = o.up;
            down = o.down;
            left = o.left;
            right = o.right;
            upRight = o.upRight;
            upLeft = o.upLeft;
            downLeft = o.downLeft;
            downRight = o.downRight;
            letter = o.letter;
        }
        return *this;
    }
    void setUp(gridNode* const changeUp)//getters and setters for each object to further satisfy parasoft
    {
        up = changeUp;
    }
    gridNode* getUp() const
    {
        return up;
    }

    void setDown(gridNode* const changeDown)
    {
        down = changeDown;
    }
    gridNode* getDown() const
    {
        return down;
    }

    void setLeft(gridNode* const changeLeft)
    {
        left = changeLeft;
    }
    gridNode* getLeft() const
    {
        return left;
    }

    void setRight(gridNode* const changeRight)
    {
        right = changeRight;
    }
    gridNode* getRight() const
    {
        return right;
    }

    void setUpRight(gridNode* const changeUpRight)
    {
        upRight = changeUpRight;
    }
    gridNode* getUpRight() const
    {
        return upRight;
    }

    void setUpLeft(gridNode* const changeUpLeft)
    {
        upLeft = changeUpLeft;
    }
    gridNode* getUpLeft() const
    {
        return upLeft;
    }

    void setDownLeft(gridNode* const changeDownLeft)
    {
        downLeft = changeDownLeft;
    }
    gridNode* getDownLeft() const
    {
        return downLeft;
    }

    void setDownRight(gridNode* const changeDownRight)
    {
        downRight = changeDownRight;
    }
    gridNode* getDownRight() const
    {
        return downRight;
    }

    void setLetter(char const changeLetter)
    {
        letter = changeLetter;
    }
    char getLetter () const
    {
        return letter;
    }
};

