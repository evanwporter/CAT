s = 'abcc'

n = len(s)

# unique_subs_lens = []
# for u in range(n):
#     for w in range(u + 1, n + 1):
#         letter_list = list(s[u:w])
#         if len(letter_list) == len(set(letter_list)):
#             unique_subs_lens.append(len(letter_list))

unique_subs_lens = [len(list(s[u:w])) for u in range(n) 
                        for w in range(u + 1, n + 1)
                        if len(s[u:w]) == len(set(s[u:w]))]

if unique_subs_lens:
    m = max(unique_subs_lens)
else: m = 0

print(m)