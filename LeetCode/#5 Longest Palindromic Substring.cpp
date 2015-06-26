#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class Solution {
public:
	string longestPalindrome(string s) {
		string sReverse = s;
		int LEN = s.size();
		reverse(sReverse.begin(), sReverse.end());
		vector<int> vec1(LEN + 1);
		vector<int> vec2(vec1);
		vector<int> &refLeft = vec1;
		vector<int> &refRight = vec2;
		vector<int> &refTemp = vec1;
		int maxLen = 0;
		int recordI = 0;
		for (int i = 0; i < LEN; i++){
			for (int j = 0; j<LEN; j++){
				if (s[i] == sReverse[j]){
					refRight[j + 1] = refLeft[j] + 1;
					if (refRight[j + 1] > maxLen){
						if (s[i]!=s[i-refRight[j+1]+1])//avoid mirror equal, optimize from substr() to tail&end
							continue;
						recordI = i;
						maxLen = refRight[j + 1];
					}
				}
			}
			refTemp = refLeft;
			refLeft = refRight;
			refRight = refTemp;
			fill(refRight.begin(), refRight.end(), 0);
		}
		return s.substr(recordI - maxLen + 1, maxLen);
	}
};

class Solution2 {
public:
	string longestPalindrome(string s) {
		int LEN = s.size();
		int startIndex = 0;
		int maxLen = 0;
		for (int i = 0; i < LEN;){
			int start = i++;
			while (s[i] == s[start]) i++;
			int end = i;
			start--;
			while (start >= 0 && end < LEN){
				if (s[start] != s[end]){
					break;
				}
				start--;
				end++;
			}
			int subLen = end - start - 1;
			if (subLen > maxLen){
				startIndex = start + 1;
				maxLen = subLen;
			}
		}
		return s.substr(startIndex,maxLen);
	}
};
/*
Solution 2 is faster than solution 1. Because I use a stupid method in Solution1...
 */

int main(){
	Solution t;
	string input = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
	string input2 = "esbtzjaaijqkgmtaajpsdfiqtvxsgfvijpxrvxgfumsuprzlyvhclgkhccmcnquukivlpnjlfteljvykbddtrpmxzcrdqinsnlsteonhcegtkoszzonkwjevlasgjlcquzuhdmmkhfniozhuphcfkeobturbuoefhmtgcvhlsezvkpgfebbdbhiuwdcftenihseorykdguoqotqyscwymtjejpdzqepjkadtftzwebxwyuqwyeegwxhroaaymusddwnjkvsvrwwsmolmidoybsotaqufhepinkkxicvzrgbgsarmizugbvtzfxghkhthzpuetufqvigmyhmlsgfaaqmmlblxbqxpluhaawqkdluwfirfngbhdkjjyfsxglsnakskcbsyafqpwmwmoxjwlhjduayqyzmpkmrjhbqyhongfdxmuwaqgjkcpatgbrqdllbzodnrifvhcfvgbixbwywanivsdjnbrgskyifgvksadvgzzzuogzcukskjxbohofdimkmyqypyuexypwnjlrfpbtkqyngvxjcwvngmilgwbpcsseoywetatfjijsbcekaixvqreelnlmdonknmxerjjhvmqiztsgjkijjtcyetuygqgsikxctvpxrqtuhxreidhwcklkkjayvqdzqqapgdqaapefzjfngdvjsiiivnkfimqkkucltgavwlakcfyhnpgmqxgfyjziliyqhugphhjtlllgtlcsibfdktzhcfuallqlonbsgyyvvyarvaxmchtyrtkgekkmhejwvsuumhcfcyncgeqtltfmhtlsfswaqpmwpjwgvksvazhwyrzwhyjjdbphhjcmurdcgtbvpkhbkpirhysrpcrntetacyfvgjivhaxgpqhbjahruuejdmaghoaquhiafjqaionbrjbjksxaezosxqmncejjptcksnoq";
	string input3 = "abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababa";
	string rt = t.longestPalindrome(input3);
	return 0;
}