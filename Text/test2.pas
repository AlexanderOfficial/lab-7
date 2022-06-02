program test2;
const//kdfkj
 pi: double = -3,1515926;
 s: integer = -6;
var
 num1: integer = 6;
 Res: double=7,123;
 Pen: double = 0;
 sashka: double = 7,123; //h
 age: integer = 1;
 x: integer = 5;
 y: integer = 7;
begin
 num1:=5;
 sashka:=20;
 Res:=(10-num1*(3 mod 1))/2;
 Pen:=((x+y) div 3) mod 5;
 write("Pen = ", Pen);
 num1:=2;
 if(sashka == 20)then
 begin
  if(3 mod 2 == 1)then
  begin
   write("How old are you?");
   Read(age);
   write("Your age = ", age);
  end
  else
  begin
   write("Res = ", pi);
  end
  write("bebebe");
 end
 else
 begin
  write("Pochti end");
  Read(sashka);
 end
 write("The END");
end.