#include "Game.h"
#include "Tetromino.h"

#include <set>
void Tetromino::renderGhostPiece(SDL_Renderer* renderer, Grid* grid)
{
    static Tetromino ghostTetro;
    ghostTetro = *this;
    ghostTetro.disableFromActivate();
    while(!ghostTetro.collision(grid, 1, 0)){
        ghostTetro.yPos++;
        ghostTetro.collin.y++;
    }
    ghostTetro.render(renderer, grid->getX(), 1);
}
// hàm random tetrads, làm giảm xác suất giống nhau của 2 khối liên tiếp
Tetromino* getRandomTetrads()
{ //...
    Tetromino* res = new Tetromino;
    static std::set<int> tetradsBag;
    if (tetradsBag.begin() == tetradsBag.end()){
        for (int i=0; i<7; i++){
            tetradsBag.insert(i);
        }
    }
    auto it = tetradsBag.begin();
    std::advance (it, rand()%tetradsBag.size());
    int pickRandOne = *it;
    *res = Tetrads[pickRandOne];
    tetradsBag.erase(tetradsBag.find(pickRandOne));
    
    return res;
}
// hàm chuyển vị ma trận (xoay khối tetrads)
void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]){
    bool backUp[sizeOfTetradsSide][sizeOfTetradsSide];
    for (int i=0; i<sizeOfTetradsSide; i++){
        for (int j=0; j<sizeOfTetradsSide; j++){
            backUp[i][j] = matrix[i][j];
        }
    }
    for (int i=0; i<sizeOfTetradsSide; i++){
        for (int j=0; j<sizeOfTetradsSide; j++){
            matrix[j][sizeOfTetradsSide-1-i] = backUp[i][j];
        }
    }
}

Tetromino::Tetromino()
{
    active = true;
    falling = false;
    pause = 0;
    startTime = 0;
}
Tetromino::Tetromino (TetroType _type, SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x, int _y, int _xPos, int _yPos)
{
    type = _type;
    active = true;
    falling = false;
    pause = 0;
    color = _color;
    collin.x = _x;
    collin.y = _y;
    collin.w = _w;
    collin.h = _h;
    xPos = _xPos;
    yPos = _yPos;
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            matrix[i][j] = _matrix[i][j];
        }
    }
}
Tetromino::~Tetromino(){}
void Tetromino::setCollinYInitTetrads(int landingPoint)
{
    yPos=landingPoint-HIDDEN_ROWS-4;            
    if (yPos+HIDDEN_ROWS<=0)
    {
        std::cout << "out of range" << std::endl;
    }
    detectCoveredRect();
}
TetroType Tetromino::getType()
{
    return type;
}
bool Tetromino::getStatus()
{
    return active;
}
void Tetromino::setActice(bool _active)
{
    active = _active;
}
bool Tetromino::getFall()
{
    return falling;
}
void Tetromino::setFall(bool fall)
{
    falling = fall;
}
int Tetromino::getXPos()
{
    return xPos;
}
int Tetromino::getYPos()
{
    return yPos;
}
void Tetromino::setXPos(int x)
{
    xPos = x;
}
void Tetromino::setYPos(int y)
{
    yPos = y;
}
int Tetromino::getXCol()
{
    return collin.x;
}
int Tetromino::getYCol()
{
    return collin.y;
}
int Tetromino::getWCol()
{
    return collin.w;
}
int Tetromino::getHCol()
{
    return collin.h;
}
void Tetromino::setPause(bool p)
{
    pause = p;
}
void Tetromino::render(SDL_Renderer* renderer, int gridXPos, bool ghost)
{ // render = toa do grid
    if (active || ghost)
    {
        for (int i=0; i<sizeOfTetradsSide; i++)
        {
            for (int j=0; j<sizeOfTetradsSide; j++)
            {
                if (matrix[i][j] == true)
                {
                    block aBlock{xPos+j, yPos+i, type};
                    aBlock.render(renderer, gridXPos, 0, ghost);
                }
            }
        }
    }
}
void Tetromino::render(SDL_Renderer* renderer, int gridXPos, int x, int y)
{ // render theo toa do thuc
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
            for (int j=0; j<sizeOfTetradsSide; j++)
            {
                if (matrix[i][j] == true)
                {
                    block aBlock{x+j*TILE_SIZE, y+i*TILE_SIZE, type, 1};
                    aBlock.render(renderer, gridXPos, 1);
                }
            }
        }
}
// tắt active
void Tetromino::disableFromActivate()
{
    falling = false;
    active = false;
}
// kết nạp khối tetrads vào grid của game
void Tetromino::mergeToGrid(Grid *grid)
{
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j] == true)
            {
                grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].type = type;
                grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].exist = true;

            }
        }
    }
}
// kiểm tra va chạm dưới

bool Tetromino::collision(Grid *grid, bool disabled, bool mergeToGrid_)
{ // ...
        int bottomSide = collin.y + collin.h;
        if ((bottomSide >= ROWS  || collisionWithOtherTetrads(grid)) && disabled)
        {
                if (mergeToGrid_)
                {
                    disableFromActivate();
                    mergeToGrid(grid);
                }
            return true;
        }
        return false;
}
//kiểm tra chồng chéo giữa các khối tetrads và tetrads với grid
bool Tetromino::checkSuperimposed(Grid *grid)
{
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j]){
                if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].exist || collin.x < 0|| collin.y < HIDDEN_ROWS*-1  || collin.x + collin.w > COLS || collin.y + collin.h > ROWS){
                    return true;
                }
            }
        }
    }
    return false;
}
// kiểm tra va chạm với các khối tetrads khác
bool Tetromino::collisionWithOtherTetrads(Grid *grid)
{ //bug
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j])
            {
                if (grid->getGrid()[i+yPos+HIDDEN_ROWS+1][j+xPos].exist)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// va chạm phải, trái
bool Tetromino::collisionWithRightTetrads(Grid *grid)
{
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j])
            {
                if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos+1].exist)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Tetromino::collisionWithLeftTetrads(Grid *grid)
{
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j])
            {
                if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos-1].exist)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Tetromino::leftCollision(Grid grid)
{ // ...
    int leftSide = collin.x;
    if (leftSide <= 0 || collisionWithLeftTetrads(&grid))
    {
        
        return true;
    }
    return false;
}
bool Tetromino::rightCollision(Grid grid)
{ // ...
    int rightSide = collin.x+collin.w;
    if (rightSide >= COLS || collisionWithRightTetrads(&grid))
    {
        return true;
    }
    return false;
}
// xác định hình chữ nhật bao quanh khối tetrads
void Tetromino::detectCoveredRect()
{ //bug
    collin.w = 0; collin.h = 0;
    for (int i=0; i<sizeOfTetradsSide; i++)
    {
        for (int j=0; j<sizeOfTetradsSide; j++)
        {
            if (matrix[i][j]!=0)
            {
                collin.h++;
                break;
            }
        }
    }
    for (int j=0; j<sizeOfTetradsSide; j++)
    {
        for (int i=0; i<sizeOfTetradsSide; i++)
        {
            if (matrix[i][j]!=0)
            {
                collin.w++;
                break;
            }
        }
    }
    bool xStop = false, yStop = false;
    for (int i=0; i<sizeOfTetradsSide && !xStop; i++)
    {
        for (int j=0; j<sizeOfTetradsSide && !xStop; j++)
        {
            if (matrix[i][j]!=0)
            {
                collin.y = yPos+i;
                xStop = true;
            }
        }
    }
    for (int j=0; j<sizeOfTetradsSide && !yStop; j++)
    {
        for (int i=0; i<sizeOfTetradsSide && !yStop; i++)
        {
            if (matrix[i][j]!=0)
            {
                collin.x = xPos+j;
                yStop = true;
            }
        }
    }
}

// hàm thực hiện hành động xoay khối ngược lại
void Tetromino::rotateBack()
{
    if (active)
    {
        transPos(matrix);
        transPos(matrix);
        transPos(matrix);
        detectCoveredRect();
    }
}
// rơi khối tetrads
void Tetromino::fall(int velocity, Grid *grid)
{
    if (active && falling && !pause)
    {
        if (startTime == 0)
        {
            startTime = SDL_GetTicks();
        }
        if (SDL_GetTicks() - startTime >= velocity)
        { // cứ mỗi velocity/1000 giây khối tetrads sẽ rơi xuống
            moveDown(grid);
            startTime = SDL_GetTicks();
        }
    }
}
// di chuyển
void Tetromino::moveUp(Grid *grid)
{
        collin.y--;
        yPos--;
}
void Tetromino::moveDown(Grid *grid, bool disable)
{
    if (!collision(grid, disable))
    {
        collin.y++;
        yPos++;
    }
}
void Tetromino::moveRight(Grid *grid)
{
    if (!rightCollision(*grid) )
    {
        collin.x++;
        xPos++;
    }
}

void Tetromino::moveLeft(Grid *grid)
{
    if (!leftCollision(*grid) )
    {
        collin.x--;
        xPos--;
    }
}
// rơi thẳng xuống nếu phím enter is pressed
void Tetromino::dropDown(Grid *grid)
{
    
    if (active && ((collin.y + collin.h - 1) < grid->getHighestRow(0, collin.x, collin.x+collin.w-1)))
    {
        while(!collision(grid))
        { //bughere
            moveDown(grid);
        }
    }
    disableFromActivate();
    
}
void Tetromino::fixTheSuperimposed(Grid *grid)
{
    if (checkSuperimposed(grid))
    {
        moveLeft(grid);
        detectCoveredRect();
        if(checkSuperimposed(grid))
        {
            moveLeft(grid);
            detectCoveredRect();
            if (checkSuperimposed(grid))
            {
                moveRight(grid);
                detectCoveredRect();
                moveRight(grid);
                detectCoveredRect();
                moveRight(grid);
                detectCoveredRect();
                if (checkSuperimposed(grid))
                {
                    moveRight(grid);
                    detectCoveredRect();
                    if (checkSuperimposed(grid))
                    {
                        moveLeft(grid);
                        detectCoveredRect();
                        moveLeft(grid);
                        detectCoveredRect();
                        moveUp(grid);
                        detectCoveredRect();
                        if (checkSuperimposed(grid))
                        {
                            moveUp(grid);
                            detectCoveredRect();
                            if (checkSuperimposed(grid))
                            {
                                moveDown(grid, 0);
                                detectCoveredRect();
                                moveDown(grid, 0);
                                detectCoveredRect();
                                moveDown(grid, 0);
                                detectCoveredRect();
                                if (checkSuperimposed(grid))
                                {
                                    moveUp(grid);
                                    detectCoveredRect();
                                    rotateBack();
                                    detectCoveredRect();
                                }
                            }
                        }
                    }    
                }
            }
        }
    }
}
// hàm xoay (fix lỗi va chạm, lỗi chồng chéo khi xoay, có thể refac để code đẹp hơn nhưng em chưa kịp làm)
void Tetromino::rotate(Grid *grid)
{
    if (active)
    {
        transPos(matrix);
        detectCoveredRect();
        fixTheSuperimposed(grid);
        detectCoveredRect();
    }
}
void Tetromino::swapWithHolding(Tetromino &holding)
{

}
