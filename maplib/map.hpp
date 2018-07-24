#ifndef MAP_RPG_GE_HPP_INCLUDED
#define MAP_RPG_GE_HPP_INCLUDED
#include <iostream>
#include <SFML/Graphics>

namespace mapper{

  namespace tools{
    std::vector<std::string> cuts(std::string const& str, std::string const& list);
  }

  template<typename T>

  typedef enum {
    up,
    right,
    down,
    left,
    floor_up,
    floor_down
  } direction6 ;

  typedef struct{
    T x,
    T y,
    T floor
  } tiny_location ;

  tiny_location build_tiny_location(T x, T y, T z);

  class location{
  public:
    location(T x, T y, T z);
    location(tiny_location const& now);
    location(tiny_location const& now, tiny_location const& previous);
    location(std::string const& code);
    tiny_location get_location(void);
    tiny_location get_prev_location(void);
    std::string write_now_code(void);
    std::string write_prev_code(void);
    location operator+(location const& a);
    location operator+(tiny_location a);
    location operator+(direction6 a);
    location operator-(location const& a);
    location operator-(tiny_location a);
    location operator-(direction6 a);
    location& operator=(location const& a);
    location& operator=(tiny_location a);
    bool operator==(location a);
    bool operator==(tiny_location a);
    bool operator!=(location a);
    bool operator!=(tiny_location a);
  protected:
    tiny_location Pnow;
    tiny_location Pprevious;
  };

  class range{
  public:
    range(void);
    range(std::string code);
    std::string write_code(void);
    range operator+(location const& a);
    range operator+(range const& a);
    range operator+(std::string code);
    range& operator=(location const& a);
    range& operator=(range const& a);
    //range operator-(location const& a);
    //range operator-(range const& a);
    bool operator==(location const& a);
    bool operator==(range const& a);
    //
    //rajouter l'opérateur !=
    //
    std::vector<blocks&> return_designated_blocks(interactive_map const& gameMap);
  protected:
    std::vector<location> blocks_pos;
    void sort(void);
  };

  class Player{

  };

  class NPC{

  };

  class Mob{

  };

  class Item{

  }

  class block{
  public:

  protected:
    location position;
    bool NPC_can_walk;
    bool Player_can_walk;
    bool Mob_can_walk;

  };

  class interactive_map{
  public:
    interactive_map(T height, T width, int bsize);
    interactive_map(std::string file);
    T define_block(std::string code, std::string PNG);
    bool set_block(T index, T height, T width);
    bool set_Player(std::shared_ptr<Player> character);
    bool set_NPC(std::shared_ptr<NPC> character);
    bool set_Mob(std::shared_ptr<Mob> character);
    Player get_Player(void);
    std::vector<std::shared_ptr<NPC> > get_all_NPCs(void);
    std::vector<std::shared_ptr<Mob> > get_all_Mobs(void);
    std::vector<std::shared_ptr<NPC> > get_NPC_in_range()
  protected:

  };
}

#endif
