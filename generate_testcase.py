filename = input('please input filename: ')

with open(filename,'w',encoding = 'utf-8') as f:
   for i in range(1660000000):
       f.write('a')