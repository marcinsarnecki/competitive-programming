for i in {1..100000}
do
	./gene $i > test.in
	./brut < test.in > brut.out
	./wzor < test.in > wzor.out
	cmp brut.out wzor.out || break
	echo $i
done
