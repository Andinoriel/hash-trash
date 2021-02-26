import 'package:ansicolor/ansicolor.dart';
import 'package:hash_trash/hash_trash.dart';

void main(List<String> arguments) {
  ansiColorDisabled = false;
  var X = getRandomX(length: 19);
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
  var collisionsX = countCollisions(hashX);
  var collisionsY = countCollisions(hashY);
  var collisionBetweenXY = countCollisionBetween(hashX, hashY);
  print('X:');
  for (var i = 0; i < hashX.length; i++) {
    print(getOutputLine(
        left: X[i],
        binLeft: binsX[i],
        binRight: binsY[i],
        collisions: collisionsX,
        hashLeft: hashX[i],
        hashRight: hashY[i]));
  }
  print('Y:');
  for (var i = 0; i < hashY.length; i++) {
    print(getOutputLine(
        left: Y[i],
        binLeft: binsY[i],
        binRight: binsX[i],
        collisions: collisionsY,
        hashLeft: hashY[i],
        hashRight: hashX[i]));
  }
  print('Correlation coefficient (X, HASH X): ' +
      correlationCoefficient(x: X, y: hashX).toStringAsFixed(2));
  print('Correlation coefficient (Y, HASH Y): ' +
      correlationCoefficient(x: Y, y: hashY).toStringAsFixed(2));
  print('Correlation coefficient (HASH X, HASH Y): ' +
      correlationCoefficient(x: hashX, y: hashY).toStringAsFixed(2));
  print('Correlation coefficient (X, Y): ' +
      correlationCoefficient(x: X, y: Y).toStringAsFixed(2));
  print('Collision in X. Collision pairs: ${collisionsX.length}');
  print('Collision in Y. Collision pairs: ${collisionsY.length}');
  print('Collision between X and Y. Collision pairs: ' +
      collisionBetweenXY.length.toString());
}
