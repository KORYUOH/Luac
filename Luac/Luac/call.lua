
function sum( x , y )
	print(""..x.. " + " ..y.. " = " ..x+y.."")
end

function power( x , y )
	sum = 1;
	for i = 0 , y do 
		sum = sum * x
	end
	print( "result = "..sum.."");
end
