#ifndef DGLW_EVENTS_HPP_
#define DGLW_EVENTS_HPP_

namespace dglw {

/**
 * An object representing a mouse button.
 */
class MouseButton {
   public:
      /**
       * MouseButton constructor
       * @param button_number The mouse button number.
       */
      MouseButton(const int button_number):
         button_number(button_number) {}

      /**
       * Sets the number of the mouse button.
       * @param button_number Number of mouse button.
       */
      void setButtonNumber(const int button_number) {
         this->button_number = button_number;
      }

      /**
       * Gets the number of the mouse button.
       * @returns the number of the mouse button.
       */
      const int getButtonNumber() const {
         return this->button_number;
      }

      /**
       * Compares to mice buttons to see if they are the same.
       * @param rhs The second button to compare.
       * @returns true if they have the same button number, otherwise false.
       */
      bool operator==(const MouseButton& rhs) const {
         return (this->button_number == rhs.button_number);
      }

      /**
       * Compares to mice buttons to see if they are differnt.
       * @param rhs The second button to compare.
       * @returns true if they have different button numbers, otherwise false.
       */
      bool operator!=(const MouseButton& rhs) const {
         return !(*this == rhs);
      }

   private:
      int button_number = 0;
};


/**
 * An object representing the coordinates of a mouse cursor.
 */
class MouseCoord{
   public:
      MouseCoord(const double xpos, const double ypos): xpos(xpos), ypos(ypos) {}

      /**
       * Gets the X component.
       * @returns The X component.
       */
      double getX() const { return xpos; }

      /**
       * Gets the Y component.
       * @return The Y component.
       */
      double getY() const { return ypos; }

      /** 
       * Compares the coordinates.
       * @param rhs Second coordinate.
       * @return true if the coordinates are the same, otherwise false.
       */
      bool operator==(const MouseCoord& rhs) const {
         return (this->getX() == rhs.getX()) && (this->getY() == rhs.getY());
      }

      /**
       * Checks if the coordinates differ.
       * @param rhs Second coordinate.
       * @returns true if the coordinates are different, otherwise false.
       */
      bool operator!=(const MouseCoord& rhs) const {
         return !(*this == rhs);
      }

      /**
       * Checks if both the X and the Y components are greator than those of another coordinate.
       * @param rhs The second coordinate to check against.
       * @return true if both X and Y are greator than those of the second coordinate.
       */
      bool operator>(const MouseCoord& rhs) const {
         return (this->getX() > rhs.getX()) && (this->getY() > rhs.getY());
      }

      /**
       * Checks if both the X and the Y components are less than those of another coordinate.
       * @param rhs The second coordinate to check against.
       * @return true if both X and Y are less than those of the second coordinate.
       */
      bool operator<(const MouseCoord& rhs) const {
         return (this->getX() < rhs.getX()) && (this->getY() < rhs.getY());
      }

      /**
       * Checks if both the X and the Y components are greator than or equal to those of another coordinate.
       * @param rhs The second coordinate to check against.
       * @return true if both X and Y are greator than those of the second coordinate.
       */
      bool operator>=(const MouseCoord& rhs) const {
         return (this->getX() >= rhs.getX()) && (this->getY() >= rhs.getY());
      }

      /**
       * Checks if both the X and the Y components are less than or equal to those of another coordinate.
       * @param rhs The second coordinate to check against.
       * @return true if both X and Y are less than those of the second coordinate.
       */
      bool operator<=(const MouseCoord& rhs) const {
         return (this->getX() <= rhs.getX()) && (this->getY() <= rhs.getY());
      }
   private:
      double xpos;
      double ypos;
};


/**
 * An object representing a mouse click event.
 **/
class MouseClick {
   public:
      /**
       * MouseClick constructor.
       * @param button The button that was clicked.
       * @param is_release True if it was a button release.
       */
      MouseClick(const MouseButton button, const bool is_release): button(button), is_release(is_release) {}

      /**
       * This returns the button that was pressed.
       * @returns The MouseButton that was pressed.
       */
      MouseButton getButton() const { return button; }

      /**
       * Gets if the button event was a release.
       * @returns true if the mouse click event was a button release. false if it was a button down.
       */
      bool isRelease() const { return is_release; }

   private:
      const MouseButton button = 0;
      const bool is_release = false;
};

} /* namespace dglw */

#endif /* DGLW_EVENTS_HPP_ */
