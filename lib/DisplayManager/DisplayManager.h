/**
 * @file DisplayManager.h
 * @brief Library for managing the MAX7219 LED matrix display using MD_Parola.
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

/**
 * @class DisplayManager
 * @brief Handles text rendering, scrolling animations, and display hardware initialization.
 */
class DisplayManager {
public:
  /**
   * @brief Constructor for DisplayManager.
   * @param hardwareType Type of the MAX7219 module (e.g., FC16_HW).
   * @param csPin Chip Select pin for the MAX7219.
   * @param maxDevices Number of daisy-chained 8x8 LED matrices.
   */
  DisplayManager(MD_MAX72XX::moduleType_t hardwareType, uint8_t csPin, uint8_t maxDevices);
  
  /**
   * @brief Initializes the LED matrix and Parola library.
   * @details Sets the brightness and initial text alignment.
   */
  void begin();

  /**
   * @brief Updates the display animations.
   * @details Must be called frequently in the main loop to ensure smooth scrolling.
   */
  void update();

  /**
   * @brief Clears the display and resets current state.
   */
  void clear();

  /**
   * @brief Shows a static or scrolling single string on the display.
   * @param text The text to be displayed.
   */
  void showText(const String& text);

  /**
   * @brief Formats and displays a track and artist name with a scrolling effect.
   * @param song Name of the track.
   * @param artist Name of the artist.
   */
  void showTrack(const String& song, const String& artist);

private:
  MD_Parola _display;
  String _currentText;
  bool _isScrolling;
};

#endif
