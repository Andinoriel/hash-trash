import 'package:ansicolor/ansicolor.dart';
import 'package:hash_trash/hash_trash.dart';
import 'package:scidart/numdart.dart';
import 'package:scidart/scidart.dart';

void main(List<String> arguments) {
  ansiColorDisabled = false;
  var X = getRandomX(length: 10);
  var Y = <int>[];
  for (var i = 0; i < X.length; i++) {
    Y.add(X[i] ^ 1 << i);
  }
  var binsX = <String>[];
  var binsY = <String>[];
  var hashX = <int>[];
  var hashY = <int>[];
  for (var x in X) {
    binsX.add(x.toRadixString(2).padLeft(20, '0'));
    hashX.add(getHash(value: x));
  }
  for (var y in Y) {
    binsY.add(y.toRadixString(2).padLeft(20, '0'));
    hashY.add(getHash(value: y));
  }
  print('X:');
  for (var i = 0; i < hashX.length; i++) {
    print(
        '${X[i].toString().padLeft(20, ' ')}\t\t${highlightDiff(left: binsX[i], right: binsY[i])}\t\tH(x)${hashX[i].toString().padLeft(20, ' ')}');
  }
  print('Y:');
  for (var i = 0; i < hashY.length; i++) {
    print(
        '${Y[i].toString().padLeft(20, ' ')}\t\t${highlightDiff(left: binsY[i], right: binsX[i])}\t\tH(x)${hashY[i].toString().padLeft(20, ' ')}');
  }
  print(
      'Correlation coefficient: ${correlationCoefficient(x: hashX, y: hashY).toStringAsFixed(2)}');
}
