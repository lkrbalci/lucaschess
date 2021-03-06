/*
    Texel - A UCI chess engine.
    Copyright (C) 2012-2013  Peter Österlund, peterosterlund2@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * computerPlayer.hpp
 *
 *  Created on: Feb 25, 2012
 *      Author: petero
 */

#ifndef COMPUTERPLAYER_HPP_
#define COMPUTERPLAYER_HPP_

#include "player.hpp"
#include "transpositionTable.hpp"
#include "book.hpp"
#include "search.hpp"

#include <string>
#include <memory>

class ComputerPlayerTest;

/**
 * A computer algorithm player.
 */
class ComputerPlayer : public Player {
    friend class ComputerPlayerTest;
public:
    static std::string engineName;
    bool verbose;

    ComputerPlayer();

    void setTTLogSize(int logSize);

    void setListener(const std::shared_ptr<Search::Listener>& listener);

    std::string getCommand(const Position& posIn, bool drawOffer, const std::vector<Position>& history);

    bool isHumanPlayer();

    void useBook(bool bookOn);

    void timeLimit(int minTimeLimit, int maxTimeLimit);

    void clearTT();

    /** Search a position and return the best move and score. Used for test suite processing. */
    std::pair<Move, std::string> searchPosition(Position& pos, int maxTimeMillis);

    /** Initialize static data. */
    static void staticInitialize();

private:
    ComputerPlayer(const ComputerPlayer& other) = delete;
    ComputerPlayer& operator=(const ComputerPlayer& other) = delete;

    /** Check if a draw claim is allowed, possibly after playing "move".
     * @param move The move that may have to be made before claiming draw.
     * @return The draw string that claims the draw, or empty string if draw claim not valid.
     */
    std::string canClaimDraw(Position& pos, std::vector<U64>& posHashList,
                             int posHashListSize, const Move& move);


    int minTimeMillis;
    int maxTimeMillis;
    int maxDepth;

    int maxNodes;
    TranspositionTable tt;
    ParallelData pd;
    std::shared_ptr<Evaluate::EvalHashTables> et;
    Book book;
    bool bookEnabled;
    Search* currentSearch;
    std::shared_ptr<Search::Listener> listener;
};


inline void
ComputerPlayer::setTTLogSize(int logSize) {
    tt.reSize(logSize);
}

inline void
ComputerPlayer::setListener(const std::shared_ptr<Search::Listener>& listener) {
    this->listener = listener;
}

inline bool
ComputerPlayer::isHumanPlayer() {
    return false;
}

inline void
ComputerPlayer::useBook(bool bookOn) {
    bookEnabled = bookOn;
}

inline void
ComputerPlayer::clearTT() {
    tt.clear();
}

#endif /* COMPUTERPLAYER_HPP_ */
