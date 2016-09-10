#include <cassert>
#include <vector>
#include <bitset>

class Solution
{
public:
   void solveSudoku(std::vector<std::vector<char>>& board) const
   {
      auto emptyCells = createEmptyCells(board);
      auto solvedCells = std::vector<SolvedCell>{};
      bool solutionFound = solveSudokuRec(emptyCells, solvedCells);
      assert(solutionFound);
      return fillBoard(board, solvedCells);
   }

private:
   struct Cell
   {
      Cell(size_t i, size_t j)
         : i(i)
         , j(j)
      {}
      size_t getId() const { return i*9 + j; }
      size_t i, j;
   };

   struct EmptyCell : public Cell
   {
      EmptyCell(size_t i, size_t j, const std::bitset<10>& possibleDigits)
         : Cell(i, j)
         , possibleDigits(possibleDigits)
      {}

      std::bitset<10> possibleDigits;
   };

   struct SolvedCell : public Cell
   {
      SolvedCell(size_t i, size_t j, size_t digit)
         : Cell(i, j)
         , digit(digit)
      {}

      size_t digit;
   };

private:
   std::vector<EmptyCell> createEmptyCells(const std::vector<std::vector<char>>& board) const
   {
      auto emptyCells = std::vector<EmptyCell>{};
      emptyCells.reserve(9*9);
      for(size_t i=0; i<board.size(); ++i)
      {
         for(size_t j=0; j<board[0].size(); ++j)
         {
            if(board[i][j] == '.')
            {
               emptyCells.emplace_back(i, j, searchInitialPossibleDigitsOfEmptyCell(i, j, board));
            }
         }
      }
      return emptyCells;
   }

   std::bitset<10> searchInitialPossibleDigitsOfEmptyCell(size_t celli, size_t cellj, const std::vector<std::vector<char>>& board) const
   {
      auto digits = std::bitset<10>{};
      
      //digit 0 is not used
      digits.set(0);

      //search clues in the same row
      for(size_t j=0; j<board[0].size(); ++j)
      {
         if(j!=cellj && board[celli][j]!='.')
         {
            digits.set(board[celli][j] - '0');
         }
      }

      //search clues in the same coloumn
      for(size_t i=0; i<board.size(); i++)
      {
         if(i!=celli && board[i][cellj]!='.')
         {
            digits.set(board[i][cellj] - '0');
         }
      }

      //search clues in the same 3x3 square
      auto upLefti = (celli / 3) * 3;
      auto upLeftj = (cellj / 3) * 3;
      for(size_t i=upLefti; i<upLefti+3; ++i)
      {
         for(size_t j=upLeftj; j<upLeftj+3; ++j)
         {
            if(i!=celli && j!=cellj && board[i][j]!='.')
            {
               digits.set(board[i][j] - '0');
            }
         }
      }
      
      digits.flip(); //convert clues to possible digits

      return digits;
   }

   bool solveSudokuRec(std::vector<EmptyCell>& emptyCells, std::vector<SolvedCell>& solvedCells) const
   {
      if(emptyCells.empty())
      {
         return true;
      }
      
      bool anyEmptyCellDoesntHavePossibleDigits = std::any_of(
            emptyCells.cbegin(),
            emptyCells.cend(),
            [](const EmptyCell& cell){ return cell.possibleDigits.count()==0; });
      if(anyEmptyCellDoesntHavePossibleDigits)
      {
         return false;
      }

      auto posMinCell = std::min_element(
         emptyCells.begin(),
         emptyCells.end(),
         [](const EmptyCell& c1, const EmptyCell& c2) { return c1.possibleDigits.count() < c2.possibleDigits.count(); });
      auto minCell = *posMinCell;
      *posMinCell = emptyCells.back();
      emptyCells.pop_back();

      for(size_t digit=1; digit<=9; ++digit)
      {
         bool digitCanBeUsed = minCell.possibleDigits.test(digit);
         if(!digitCanBeUsed)
            continue;
         
         auto removed = removeDigitFromEmptyCells(minCell, digit, emptyCells);
         if(solveSudokuRec(emptyCells, solvedCells))
         {
            solvedCells.emplace_back(minCell.i, minCell.j, digit);
            return true;
         }
         undoRemoveDigitFromEmptyCells(digit, emptyCells, removed);
      }
      emptyCells.push_back(std::move(minCell));
      return false;
   }


   std::bitset<9*9> removeDigitFromEmptyCells(const Cell& cell, size_t digit, std::vector<EmptyCell>& emptyCells) const
   {
      auto removed = std::bitset<9*9>{};
      
      for(auto& emptyCell : emptyCells)
      {
         bool isSameRow = emptyCell.i == cell.i;
         bool isSameCol = emptyCell.j == cell.j;
         bool isSameSquare = (emptyCell.i/3 == cell.i/3) && (emptyCell.j/3 == cell.j/3);
         bool emptyCellHasDigit = emptyCell.possibleDigits.test(digit);
         if((isSameRow || isSameCol || isSameSquare) && emptyCellHasDigit)
         {
            emptyCell.possibleDigits.reset(digit);
            removed.set(emptyCell.getId());
         }
      }

      return removed;
   }

   void undoRemoveDigitFromEmptyCells(size_t digit, std::vector<EmptyCell>& emptyCells, const std::bitset<9*9>& removed) const
   {
      for(auto& emptyCell : emptyCells)
      {
         bool digitWasRemovedFromThisCell = removed.test(emptyCell.getId());
         if(digitWasRemovedFromThisCell)
         {
            emptyCell.possibleDigits.set(digit);
         }
      }
   }

   void fillBoard(std::vector<std::vector<char>>& board, const std::vector<SolvedCell>& solvedCells) const
   {
      for(const auto& solvedCell : solvedCells)
      {
         board[solvedCell.i][solvedCell.j] = solvedCell.digit + '0';
      }
   }
};

