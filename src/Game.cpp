#include "Game.h"

#include "Input.h"
#include <random>

Game::Game(vec2<int> SizeOfWorld) :
    Size(SizeOfWorld)
{
    this->SnakePtr = nullptr;
    this->RenderPtr = nullptr;
}

Game::~Game()
{
}

void Game::play()
{
    this->initEntities();

    while (true)
    {
        this->RenderPtr->render(this->getRednderInfo());
        Input::getInput();
        
        auto CurrentInput = Input::LastInput;

        if (CurrentInput.Type == InputType::KEYBOARD_EVENT)
        {

            switch (CurrentInput.KeyboardType)
            {
            case KeyboardEventType::UP:
                this->SnakePtr->move(MoveDirection::UP);
                break;
            case KeyboardEventType::DOWN:
                this->SnakePtr->move(MoveDirection::DOWN);
                break;
            case KeyboardEventType::LEFT:
                this->SnakePtr->move(MoveDirection::LEFT);
                break;
            case KeyboardEventType::RIGHT:
                this->SnakePtr->move(MoveDirection::RIGHT);
                break;
            default:
                break;
            }

            if (this->SnakePtr->isHitItself())
                return;
        }
        else if (CurrentInput.Type == InputType::WINDOW_EVENT)
        {
            switch (CurrentInput.WindowType)
            {
            case WindowEventType::WINDOW_CLOSED:
                return;
            case WindowEventType::WINDOW_RESIZE:
                continue;
            default:
                break;
            }
        }
    }
}

ObjectType Game::getTypeOfObject(vec2<int> Coordinate)
{
    if (this->Treat != nullptr)
    {
        if (this->Treat->getPosition() == Coordinate)
            return ObjectType::TREAT;
    }

    auto SnakeInfo = this->SnakePtr->getRenderInfo();

    for (auto Body : SnakeInfo)
    {
        if (Body.Position == Coordinate)
            return ObjectType::BODY;
    }

    return ObjectType::NONE;
}

vec2<int> Game::getWorldSize()
{
    return this->Size;
}

void Game::eatTreat()
{
    this->Treat = nullptr;

    this->spawnNewTreat();
}

void Game::spawnNewTreat()
{
    auto SnakeInfo = this->SnakePtr->getRenderInfo();

    if (SnakeInfo.size() == this->Size.x * this->Size.y)
        return;

    std::vector<vec2<int>> PosiblePositions = {};

    for (int y = 0; y < Size.y; y++)
    {
        for (int x = 0; x < Size.x; x++)
        {
            PosiblePositions.push_back(vec2<int>(x, y));
        }
    }

    for (auto BodyCell : SnakeInfo)
    {
        for (int Index = 0; Index < PosiblePositions.size(); Index++)
        {
            auto PosibleCell = PosiblePositions.begin() + Index;

            if (BodyCell.Position == *PosibleCell)
            {
                PosiblePositions.erase(PosibleCell);
                break;
            }
        }
    }

    std::random_device rd;

    std::uniform_int_distribution<int> dist(0, PosiblePositions.size() - 1);

    int NewPosition = dist(rd);

    this->Treat = std::make_unique<Object>(PosiblePositions.at(NewPosition));
}

RenderInfo Game::getRednderInfo()
{
    RenderInfo Result;

     Result.SnakeInfo = this->SnakePtr->getRenderInfo();

     if (Treat != nullptr)
         Result.TreatInfo = { ObjectType::TREAT, this->Treat->getPosition() };
     else
         Result.TreatInfo = { ObjectType::TREAT, vec2<int>(-1,-1) };

     Result.Size = this->Size;

     return Result;
}

void Game::initEntities()
{
    this->SnakePtr = std::make_unique<Snake>(this, vec2<int>(1, 2), vec2<int>(2, 2));

    this->RenderPtr = std::make_unique<Render>();

    this->spawnNewTreat();
}
