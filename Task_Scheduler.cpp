class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for(char c:tasks) freq[c-'A']++;
        sort(freq.begin(),freq.end(),greater<int>());
        int maxFreq=freq[0];
        int slots=(maxFreq-1)*(n+1)+1;
        int i=1;
        while(i<26&&freq[i]==maxFreq){
            slots++;
            i++;
        }
        return max((int)tasks.size(),slots);
    }
};
