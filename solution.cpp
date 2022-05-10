#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <bitset>
using namespace sol1092;
using namespace std;

/*takeaways
  - create a dp to record the longest common subsequence
      c  a  b
    a 0  1  1
    b 0  1  2
    a 0  1  2
    c 1  1  2
    - let's look at dp[2][3] = 2 (one-based)
      s1[1] == s2[2] == 'b'
      - so dp[2][3] would just extend dp[1][2] by 1
    - dp[i][j] means for s1[0..i-1], s2[0..j-1] what
      is the length for the lcs between them
    - let's look at dp[3][3]
      - s1[2] != s2[2] as 'a' != 'b'
      - you can add s1[2] which is 'a' or s2[2] which
        is 'b' to get to dp[3][3]
      - dp[2][3] -> dp[3][3] (if we carry over this by adding s1[2])
        or
      - dp[3][2] -> dp[3][3] (if we carry over this by adding s2[2])
      - we will choose which one is bigger to continue our path
        as we are looking for LCS
      - we will choose dp[2][3] in this case so we will add s1[2]

  - base on the dp we can create the super sequence
    - do it backward and use the dp to decide which one to pick
      the next char one if the next char is not part of the lcs



*/

string Solution::findShortest(string s1, string s2)
{
  int len1 = s1.size(), len2 = s2.size();
  /*
    dp[i][j]: the length of the longest common subsequence
              between s1[0..i-1] and s2[0..j-1]
    - we have dp[0..s1.size()-1][0] = 0 and dp[0][0..s2.size()-1]=0
      so the code will be simpler

  */
  auto dp = vector<vector<int>>(len1 + 1, vector<int>(len2 + 1));

  /* find the longest common subsequence between s1 and s2 */

  for (auto i = 1; i <= len1; i++)
    for (auto j = 1; j <= len2; j++)
    {
      /* made the same mistake again
         - ith char in s is s1[i-1] not s1[i]!!
      */
      if (s1[i - 1] == s2[j - 1])
        /* add 1 to the path before we add s1[i-1] and s2[j-1] */
        dp[i][j] = dp[i - 1][j - 1] + 1;
      /* carry over
         - two paths to come to dp[i][j]
           - from dp[i-1][j] by adding s1[i]
             - walking down from dp[i-1][j]
           - from dp[i][j-1] by adding s2[j]
             - walking right from dp[i][j-1]
           - notice no matter you are
             from dp[i-1][j] or dp[i][j-1]
             the char at either s2[j-1] (dp[i-1][j])
             or s1[i-1] (dp[i][j-1])  has been accounted
             for, so if s1[i-1] == s2[j-1] we
             can't just add 1 to the max of these
             two as we will over count it
      */
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }

  /* we now add chars from s1 and s2 there are not part of
     the lcs to the lcs to create the super sequence
     - walking backward in the dp to find the super sequence
  */

  auto chars = deque<char>();
  while (len1 || len2)
  {
    char c;
    if (len1 == 0)
      /* ran out of s1
         - copy remaining chars from s2
      */
      c = s2[--len2];
    else if (len2 == 0)
      c = s1[--len1];
    else if (s1[len1 - 1] == s2[len2 - 1])
      /* char is in lcs
         - consume one char from both s1 and s2
      */
      c = s1[--len1] = s2[--len2];
    /* char from s1 and is not in lcs */
    else if (dp[len1][len2] == dp[len1 - 1][len2])
      /* moving down from dp[len-1][len2]
         - and how do we move down from the
           some column? we add s1[len1-1]
         - why we check this path first?
           - it doesn't matter as the super sequence
             is not unique any way; you can choose
             the other path as well
      */
      c = s1[--len1];
    /* char from s2 and is not in lcs */
    else if (dp[len1][len2] == dp[len1][len2 - 1])
      /* add s2[len2-1] to get to dp[len1][len2] as
         the path is coming from the left
      */
      c = s2[--len2];
    /* we are doing it backward */
    chars.push_front(c);
  }

  return {begin(chars), end(chars)};
}