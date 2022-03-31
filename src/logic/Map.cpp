#include "logic/Map.hpp"
#include "entity/EntityMap.hpp"
#include "square/SquareMap.hpp"
#include "util/Util.hpp"

Map::Map(std::string path, const ElementsConfig& display) : display(display) {
    std::ifstream file(path);
    std::string buffer;

    if (!file) throw std::invalid_argument("Impossible d'ouvrir le fichier");

    std::stringstream strs;
    strs << file.rdbuf();
    strmap = strs.str();

    if (!(width = is_length_equal(strmap, '\n'))) throw std::invalid_argument("Le format de la carte est invalide !");

    height = get_nb_lines(strmap, '\n') + 1;
    rm_spaces(strmap);

    logic_size = width * height;
    logic_map = new Tile*[logic_size];

    for (int x = 0; x < logic_size; x++) {
        logic_map[x] = new Tile(this, Position(x / width, x % width));
        Entity* entity = make_entity(strmap[x], logic_map[x]);
        Square* square = make_square(strmap[x], logic_map[x]);
        if (square == NULL) square = make_square('_', logic_map[x]);

        logic_map[x]->setEntity(entity);
        logic_map[x]->setSquare(square);
    }
}

Map::~Map() {
    for (int x = 0; x < logic_size; x++) {
        if (logic_map[x] != NULL) delete logic_map[x];
    }

    if (logic_map != NULL) delete[] logic_map;
}

const std::string& Map::get_str() const {
    return this->strmap;
}

Tile* Map::getTileAtPos(int x, int y) const {
    return getTileAtPos(Position(x, y));
}

Tile* Map::getTileAtPos(const Position pos) const {
    if (pos.getX() >= height || pos.getY() >= width || pos.getX() < 0 || pos.getY() < 0) {
        return NULL;
    }
    return this->logic_map[pos.getX() * width + pos.getY()];
}

const ElementsConfig& Map::getConfig() const {
    return display;
}

std::ostream& operator<<(std::ostream& out, const Map& map) {
    for (int x = 0; x < map.logic_size; x++) {
        out << *(map.logic_map[x]);
        if ((x + 1) % map.width == 0) out << '\n';
    }

    return out;
}