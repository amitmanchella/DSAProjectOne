#include "maze.hpp"
#include "cyclic_double_queue.hpp"

using namespace cs251;

/**
bool maze::has_valid_move(Coordinate coordinate, Direction direction) {
    Direction direction1 = direction;
    size_t x = coordinate.x;
    size_t y = coordinate.y;
    size_t z = coordinate.z;
    switch (direction) {
        case static_cast<int>(cs251::Direction::Right):
            if (x < m_dimX - 1)
                return true;
        case static_cast<int>(cs251::Direction::Left):
            if (x > 0)
                return true;
        case static_cast<int>(cs251::Direction::Top):
            if (y < m_dimY - 1)
                return true;
        case static_cast<int>(cs251::Direction::Bottom):
            if (y > 0)
                return true;
        case static_cast<int>(cs251::Direction::Back):
            if (z < m_dimZ - 1)
                return true;
        case static_cast<int>(cs251::Direction::Front):
            if (z > 0)
                return true;
    }
    return false;
}
 **/
void maze::break_walls(Direction direction, Coordinate coordinate) {
    if (direction == Direction::Right) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 1;
    }
    else if (direction == Direction::Left) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 2;
    }
    else if (direction == Direction::Front) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 32;
    }
    else if (direction == Direction::Back) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 16;

    }
    else if (direction == Direction::Top) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 4;

    }
    else if (direction == Direction::Bottom) {
        m_map[get_index(coordinate.x, coordinate.y, coordinate.z)] -= 8;
    }
    return;
}

bool maze::has_valid_move(Coordinate coordinate) {
    size_t x = coordinate.x;
    size_t y = coordinate.y;
    size_t z = coordinate.z;
    if (x < m_dimX - 1 && m_map[get_index(coordinate.x + 1, coordinate.y, coordinate.z)] <= 63)
        return true;
    if (x > 0 && m_map[get_index(coordinate.x - 1, coordinate.y, coordinate.z)] <= 63)
        return true;
    if (y < m_dimY - 1 && m_map[get_index(coordinate.x, coordinate.y + 1, coordinate.z)] <= 63)
        return true;
    if (y > 0 && m_map[get_index(coordinate.x, coordinate.y - 1, coordinate.z)] <= 63)
        return true;
    if (z < m_dimZ - 1 && m_map[get_index(coordinate.x, coordinate.y, coordinate.z + 1)] <= 63)
        return true;
    if (z > 0 && m_map[get_index(coordinate.x, coordinate.y, coordinate.z - 1)] <= 63)
        return true;
    return false;
}

void maze::initialize(const size_t dimX, const size_t dimY, const size_t dimZ, unsigned seed)
{
    m_dimX = dimX;
    m_dimY = dimY;
    m_dimZ = dimZ;
    size_t totalValue = dimX * dimY * dimZ;
    m_map = new unsigned[totalValue];
    cyclic_double_queue<Coordinate> queue(10, 2, 3);
    for (size_t i = 0; i < totalValue; i++) {
        m_map[i] = 63;
    }
    Coordinate coordinate = {0,0,0};
    queue.enqueue_back(coordinate);
    while (queue.get_size() != 0) {
        Coordinate coordinateTemp = queue.back();
        if (((m_map[get_index(coordinateTemp.x, coordinateTemp.y, coordinateTemp.z)] & (unsigned int) Direction::Mark) != 64)) {
            m_map[get_index(coordinateTemp.x, coordinateTemp.y, coordinateTemp.z)] += 64; //indicating it is a now visited index
        }
        Direction direction = get_next_direction(seed);
        bool checker = false;
        int num = 0;
        while (!checker) {
            if (num == 6) {
                break;
            }
            if (direction == Direction::Right) {
                if (coordinateTemp.x >= m_dimX - 1 || m_map[get_index(coordinateTemp.x + 1, coordinateTemp.y, coordinateTemp.z)] > 63) {
                    direction = Direction::Left;
                }
                else {
                    break_walls(Direction::Right, coordinateTemp);
                    coordinateTemp.x += 1;
                    break_walls(Direction::Left, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            else if (direction == Direction::Left) {
                if (coordinateTemp.x <= 0 || m_map[get_index(coordinateTemp.x - 1, coordinateTemp.y, coordinateTemp.z)] > 63) {
                    direction = Direction::Top;
                } else {
                    break_walls(Direction::Left, coordinateTemp);
                    coordinateTemp.x -= 1;
                    break_walls(Direction::Right, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            else if (direction == Direction::Top) {
                if (coordinateTemp.y >= m_dimY - 1 || m_map[get_index(coordinateTemp.x, coordinateTemp.y + 1, coordinateTemp.z)] > 63) {
                    direction = Direction::Bottom;
                } else {
                    break_walls(Direction::Top, coordinateTemp);
                    coordinateTemp.y += 1;
                    break_walls(Direction::Bottom, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            else if (direction == Direction::Bottom) {
                if (coordinateTemp.y <= 0 || m_map[get_index(coordinateTemp.x, coordinateTemp.y - 1, coordinateTemp.z)] > 63) {
                    direction = Direction::Back;
                } else {
                    break_walls(Direction::Bottom, coordinateTemp);
                    coordinateTemp.y -= 1;
                    break_walls(Direction::Top, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            else if (direction == Direction::Back) {
                if (coordinateTemp.z >= m_dimZ - 1 || m_map[get_index(coordinateTemp.x, coordinateTemp.y, coordinateTemp.z + 1)] > 63) {
                    direction = Direction::Front;
                } else {
                    break_walls(Direction::Back, coordinateTemp);
                    coordinateTemp.z += 1;
                    break_walls(Direction::Front, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            else if (direction == Direction::Front) {
                if (coordinateTemp.z <= 0 || m_map[get_index(coordinateTemp.x, coordinateTemp.y, coordinateTemp.z - 1)] > 63) {
                    direction = Direction::Right;
                } else {
                    break_walls(Direction::Front, coordinateTemp);
                    coordinateTemp.z -= 1;
                    break_walls(Direction::Back, coordinateTemp);
                    queue.enqueue_back(coordinateTemp);
                    checker = true;
                }
            }
            num++;
        }
        if (!checker) {
            queue.dequeue_back();
        }
    }

}
bool maze::solve(const size_t startX, const size_t startY, const size_t startZ, const  size_t endX, const size_t endY, const size_t endZ) {
    /*
    m_map = new unsigned[totalValue];
    cyclic_double_queue<Coordinate> queue(10, 2, 3);
    for (size_t i = 0; i < totalValue; i++) {
        m_map[i] = 63;
    }
    Coordinate start = {startX, startY,startZ};
    Coordinate coordinate = {startX, startY,startZ};
    Coordinate end = {endX, endY, endZ};


    queue.enqueue_back(start);
    unsigned int *maze = new unsigned [totalValue];
    while (queue.get_size() != 0) {
        if ((coordinate.x == end.x) && (coordinate.y == end.y) && (coordinate.z == end.z)) {
            break;
        }
    }

    coordinate.x = end.x;
    coordinate.y = end.y;
    coordinate.z = end.z;

     */
    size_t totalValue = m_dimX * m_dimY * m_dimZ;
    for (size_t i = 0; i < totalValue; i++) {
        if (m_map[i] > 63) {
            m_map[i] -= 64;
        }
    }
    cyclic_double_queue<Coordinate> queue;
    Coordinate start = {startX, startY, startZ};
    queue.enqueue_back(start);

    // Initialize a "previous" array of the same size as the map
    Coordinate* previous = new Coordinate[totalValue];
    Coordinate ender = {0,0,0};

    // Mark the start point as visited DOES THIS NEED TO HAPPEN?
    //m_map[get_index(start.x, start.y, start.z)] |= static_cast<unsigned>(Direction::Mark);

    // Loop until the queue is empty
    while (!queue.empty()) {
        // Dequeue current index and mark it as visited.
        Coordinate current = queue.dequeue_front();
        m_map[get_index(current.x, current.y, current.z)] |= static_cast<unsigned>(Direction::Mark);

        // If current index is the end point
        if (current.x == endX && current.y == endY && current.z == endZ) {
            ender = current;
            break;
        }

        // For each valid, unvisited neighbor of the current index
        Direction d_list[6] = {Direction::Right, Direction::Left, Direction::Top, Direction::Bottom, Direction::Back, Direction::Front};
        for (Direction dir : d_list) {
            Coordinate next = current; // Prepare the next coordinate

            // Adjust next based on direction

            if (((unsigned int) dir & (m_map[get_index(next.x, next.y, next.z)])) == 0) {
                switch ((unsigned int) dir) {
                    case (unsigned int) Direction::Right:
                        next.x++;
                        break;
                    case (unsigned int) Direction::Left:
                        next.x--;
                        break;
                    case (unsigned int) Direction::Top:
                        next.y++;
                        break;
                    case (unsigned int) Direction::Bottom:
                        next.y--;
                        break;
                    case (unsigned int) Direction::Back:
                        next.z++;
                        break;
                    case (unsigned int) Direction::Front:
                        next.z--;
                        break;
                    default:
                        continue;
                }
                size_t nextIndex = get_index(next.x, next.y, next.z);

                // Check bounds and if the next cell is already visited
                if (next.x < m_dimX && next.y < m_dimY && next.z < m_dimZ && !(m_map[nextIndex] & static_cast<unsigned>(Direction::Mark))) {// what does this last condition do
                    // Mark the cell as visited
                    m_map[nextIndex] |= static_cast<unsigned>(Direction::Mark);

                    // Set the neighbor's "previous" index to the current index
                    previous[nextIndex] = current;

                    // Enqueue the neighbor's index
                    queue.enqueue_back(next);
                }
            }
            else {
                continue;
            }


        }
    }
    // Set the current index to the end point
    size_t currentIndex = get_index(endX, endY, endZ);
    // Loop until the current index is the start point
    // Reset the entire matrix back to 0
    for (size_t i = 0; i < totalValue; i++) {
        if (m_map[i] > 63) {
            m_map[i] -= 64;
        }
    }

    while (currentIndex != get_index(start.x, start.y, start.z)) {
        // Mark the current index as part of the path using Direction::Mark
        m_map[currentIndex] |= static_cast<unsigned>(Direction::Mark);

        // Set the current index to its "previous" index
        ender = previous[currentIndex];

        if (get_index(ender.x, ender.y, ender.z) == 0) {
            break;
        }

        currentIndex = get_index(ender.x, ender.y, ender.z);
    }

    // Mark the start index as part of the path using Direction::Mark
    m_map[get_index(start.x, start.y, start.z)] |= static_cast<unsigned>(Direction::Mark);
    //delete[] previous;
    return true; // Path found

    // If no path is found
}



std::string maze::print_walls(const size_t z) const {
    std::stringstream status;
    for (size_t x = 0; x < m_dimX; x++) {
        status << "+---";
    }
    status << "+\n";

    for (size_t y = 0; y < m_dimY; y++) {
        for (size_t x = 0; x < m_dimX; x++) {
            if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Left)) != 0) {
                status << "|";
            } else {
                status << " ";
            }
            if (((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Front)) != 0) &&
                ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Back)) != 0)) {
                status << " X ";
            }
            else if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Front)) != 0) {
                status << " F ";
            }
            else if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Back)) != 0) {
                status << " B ";
            }
            else {
                status << "   ";
            }
        }
        status << "|\n";

        for (size_t x = 0; x < m_dimX; x++) {
            if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Top)) != 0) {
                status << "+---";
            } else {
                status << "+   ";
            }
        }
        status << "+\n";
    }
    return status.str();
}

std::string maze::print_marks(const size_t z) const
{
    std::stringstream status;
    for (size_t x = 0; x < m_dimX; x++) {
        status << "+---";
    }
    status << "+\n";

    for (size_t y = 0; y < m_dimY; y++) {
        for (size_t x = 0; x < m_dimX; x++) {
            if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Left)) != 0) {
                status << "|";
            } else {
                status << " ";
            }
            if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Mark)) != 0) {
                status << " # ";
            }
            else {
                status << "   ";
            }
        }
        status << "|\n";

        for (size_t x = 0; x < m_dimX; x++) {
            if ((m_map[get_index(x,y,z)] & static_cast<int>(Direction::Top)) != 0) {
                status << "+---";
            } else {
                status << "+   ";
            }
        }
        status << "+\n";
    }
    return status.str();
}

void maze::get_dim(size_t& dimX, size_t& dimY, size_t& dimZ) const
{
    dimX = m_dimZ;
    dimY = m_dimY;
    dimZ = m_dimZ;
}

Direction maze::get_next_direction(unsigned& seed)
{
    //Please do not modify this function!
    //Any modification of this function may result in a zero for all grading cases.
    std::mt19937 gen(seed);
    seed = gen();
    return static_cast<Direction>(1 << seed % 6);
}

size_t maze::get_index(const size_t x, const size_t y, const size_t z) const {
    size_t index = x + (y * m_dimX) + (z * m_dimX * m_dimY);
    return index;
}
