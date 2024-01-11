/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Utils.hpp
*/

#ifndef raylib_UTILS_HPP
#define raylib_UTILS_HPP

#include <raylib.h>
#include <iostream>
#include <raymath.h>

namespace RL {

    class Utils {
        public:
            static void setClipboardText(const std::string &text) {
                return SetClipboardText(text.c_str());
            };

            static const std::string getClipboardText() {
                return GetClipboardText();
            };

            static void waitTime(double seconds) {
                return WaitTime(seconds);
            };

            static void setTargetFPS(int fps) {
                return SetTargetFPS(fps);
            };

            static int getFPS() {
                return GetFPS();
            };

            static float getFrameTime() {
                return GetFrameTime();
            };

            static void setLoadFileDataCallback(LoadFileDataCallback callback) {
                return SetLoadFileDataCallback(callback);
            };

            static void setSaveFileDataCallback(SaveFileDataCallback callback) {
                return SetSaveFileDataCallback(callback);
            };

            static void setLoadFileTextCallback(LoadFileTextCallback callback) {
                return SetLoadFileTextCallback(callback);
            };

            static void setSaveFileTextCallback(SaveFileTextCallback callback) {
                return SetSaveFileTextCallback(callback);
            };

            static unsigned char *loadFileData(const std::string &fileName, int *bytesRead) {
                return LoadFileData(fileName.c_str(), bytesRead);
            };

            static void unloadFileData(unsigned char *data) {
                return UnloadFileData(data);
            };

            static bool saveFileData(const std::string &fileName, void *data, unsigned int bytesToWrite) {
                return SaveFileData(fileName.c_str(), data, bytesToWrite);
            };

            static bool exportDataAsCode(unsigned char *data, const unsigned char size, const std::string& fileName) {
                return ExportDataAsCode(data, size, fileName.c_str());
            };

            static std::string loadFileText(const std::string &fileName) {
                return LoadFileText(fileName.c_str());
            };

            static void unloadFileText(std::string &text) {
                return UnloadFileText((char *) text.c_str());
            };

            static bool saveFileText(const std::string &fileName, std::string &text) {
                return SaveFileText(fileName.c_str(), (char *) text.c_str());
            };

            static bool fileExists(const std::string &fileName) {
                return FileExists(fileName.c_str());
            };

            static bool directoryExists(const std::string &dirPath) {
                return DirectoryExists(dirPath.c_str());
            };

            static bool isFileExtension(const std::string &fileName, const std::string &ext) {
                return IsFileExtension(fileName.c_str(), ext.c_str());
            };

            static int getFileLength(const std::string &fileName) {
                return GetFileLength(fileName.c_str());
            };

            static std::string getFileExtension(const std::string& fileName) {
                return GetFileExtension(fileName.c_str());
            };

            static std::string getFileName(const std::string& filePath) {
                return GetFileName(filePath.c_str());
            };

            static std::string getFileNameWithoutExt(const std::string& filePath) {
                return GetFileNameWithoutExt(filePath.c_str());
            };

            static std::string getDirectoryPath(const std::string& filePath) {
                return GetDirectoryPath(filePath.c_str());
            };

            static std::string getPrevDirectoryPath(const std::string& dirPath) {
                return GetPrevDirectoryPath(dirPath.c_str());
            };

            static std::string getWorkingDirectory() {
                return GetWorkingDirectory();
            };

            static std::string getApplicationDirectory() {
                return GetApplicationDirectory();
            };

            static bool changeDirectory(const std::string& dir) {
                return ChangeDirectory(dir.c_str());
            };

            static bool isPathFile(const std::string& path) {
                return IsPathFile(path.c_str());
            };

            static FilePathList loadDirectoryFiles(const std::string& dirPath) {
                return LoadDirectoryFiles(dirPath.c_str());
            };

            static FilePathList loadDirectoryFilesEx(const std::string& basePath, const std::string &filter, bool scanSubdirs) {
                return LoadDirectoryFilesEx(basePath.c_str(), filter.c_str(), scanSubdirs);
            };

            static void unloadDirectoryFiles(FilePathList files) {
                return UnloadDirectoryFiles(files);
            };

            static bool isFileDropped() {
                return IsFileDropped();
            };

            static FilePathList loadDroppedFiles() {
                return LoadDroppedFiles();
            };

            static void unloadDroppedFiles(FilePathList files) {
                return UnloadDroppedFiles(files);
            };

            static long getFileModTime(const std::string &fileName) {
                return GetFileModTime(fileName.c_str());
            };

            static unsigned char * compressData(unsigned char *data, int dataSize, int *compDataSize) {
                return CompressData(data, dataSize, compDataSize);
            };

            static unsigned char * decompressData(unsigned char *compData, int compDataSize, int *dataSize) {
                return DecompressData(compData, compDataSize, dataSize);
            };

            static std::string encodeDataBase64(unsigned char *data, int dataSize, int *outputSize) {
                return EncodeDataBase64(data, dataSize, outputSize);
            };

            static unsigned char * decodeDataBase64(unsigned char *data, int *outputSize) {
                return DecodeDataBase64(data, outputSize);
            };

            static bool checkCollisionRecs(Rectangle rec1, Rectangle rec2) {
                return CheckCollisionRecs(rec1, rec2);
            };

            static bool checkCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2) {
                return CheckCollisionCircles(center1, radius1, center2, radius2);
            };

            static bool checkCollisionCircleRec(Vector2 center, float radius, Rectangle rec) {
                return CheckCollisionCircleRec(center, radius, rec);
            };

            static bool checkCollisionPointRec(Vector2 point, Rectangle rec) {
                return CheckCollisionPointRec(point, rec);
            };

            static bool checkCollisionPointCircle(Vector2 point, Vector2 center, float radius) {
                return CheckCollisionPointCircle(point, center, radius);
            };

            static bool checkCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3) {
                return CheckCollisionPointTriangle(point, p1, p2, p3);
            };

            static bool checkCollisionPointPoly(Vector2 point, Vector2 *points, int pointCount) {
                return CheckCollisionPointPoly(point, points, pointCount);
            };

            static bool checkCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint) {
                return CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, collisionPoint);
            };

            static bool checkCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold) {
                return CheckCollisionPointLine(point, p1, p2, threshold);
            };

            static Rectangle getCollisionRec(Rectangle rec1, Rectangle rec2) {
                return GetCollisionRec(rec1,rec2);
            };

            static VrStereoConfig loadVrStereoConfig(VrDeviceInfo device) {
                return LoadVrStereoConfig(device);
            };

            static void unloadVrStereoConfig(VrStereoConfig config) {
                return UnloadVrStereoConfig(config);
            };

            static double getTime() {
                return GetTime();
            };

            static int getRandomValue(int min, int max) {
                return GetRandomValue(min, max);
            };

            static void setRandomSeed(unsigned int seed) {
                return SetRandomSeed(seed);
            };

            static void setConfigFlags(unsigned int flags) {
                return SetConfigFlags(flags);
            };

            static void setTraceLogLevel(int logLevel) {
                return SetTraceLogLevel(logLevel);
            };

            static void openURL(const std::string &url) {
                return OpenURL(url.c_str());
            };

            static void setTraceLogCallback(TraceLogCallback callback) {
                return SetTraceLogCallback(callback);
            };

            static Color fade(Color color, float alpha) {
                return Fade(color, alpha);
            };

            static int colorToInt(Color color) {
                return ColorToInt(color);
            };

            static Vector4 colorNormalize(Color color) {
                return ColorNormalize(color);
            };

            static Color colorFromNormalized(Vector4 normalized) {
                return ColorFromNormalized(normalized);
            };

            static Vector3 colorToHSV(Color color) {
                return ColorToHSV(color);
            };

            static Color colorFromHSV(float hue, float saturation, float value) {
                return ColorFromHSV(hue, saturation, value);
            };

            static Color colorTint(Color color, Color tint) {
                return ColorTint(color, tint);
            };

            static Color colorBrightness(Color color, float factor) {
                return ColorBrightness(color, factor);
            };

            static Color colorContrast(Color color, float contrast) {
                return ColorContrast(color, contrast);
            };

            static Color colorAlpha(Color color, float alpha) {
                return ColorAlpha(color, alpha);
            };

            static Color colorAlphaBlend(Color dst, Color src, Color tint) {
                return ColorAlphaBlend(dst, src, tint);
            };

            static Color getColor(unsigned int hexValue) {
                return GetColor(hexValue);
            };

            static Color getPixelColor(void *srcPtr, int format) {
                return GetPixelColor(srcPtr, format);
            };

            static void setPixelColor(void *dstPtr, Color color, int format) {
                return SetPixelColor(dstPtr, color, format);
            };

            static int getPixelDataSize(int width, int height, int format) {
                return GetPixelDataSize(width, height, format);
            };

            static void drawBoundingBox(BoundingBox box, Color color) {
                return DrawBoundingBox(box, color);
            };

            static bool checkCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2) {
                return CheckCollisionSpheres(center1, radius1, center2, radius2);
            };

            static bool checkCollisionBoxes(BoundingBox box1, BoundingBox box2) {
                return CheckCollisionBoxes(box1, box2);
            };

            static bool checkCollisionBoxSphere(BoundingBox box, Vector3 center, float radius) {
                 return CheckCollisionBoxSphere(box, center, radius);
            };

            static int measureText(const std::string &text, int fontSize) {
                return MeasureText(text.c_str(), fontSize);
            }

            static Matrix matrixRotate(Vector3 axis, float angle) {
                return MatrixRotate(axis, angle);
            };

            static Vector2 getMousePosition() {
                return GetMousePosition();
            }

            static bool isKeyPressed(int key) {
                return IsKeyPressed(key);
            };

            static bool isKeyDown(int key) {
                return IsKeyDown(key);
            };
    };

} // RayGui

#endif //raylib_UTILS_HPP
