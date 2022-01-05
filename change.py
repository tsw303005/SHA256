'''
use this python code to change the hash formate we want
'''

a = input('')

print('{', end = '')

str = ['0x' + a[i:i+2] for i in range(0, len(a), 2)]
result = (',').join(str)
print(result, end='}\n')