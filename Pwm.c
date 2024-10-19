#include "Pwm.h"

static Pwm_ConfigType
    PwmChannelConfig[1]; // Assuming 1 PWM channel for simplicity
static boolean PwmInitialized = FALSE;

// Function to initialize PWM
void Pwm_Init(const Pwm_ConfigType *ConfigPtr) {
  if (PwmInitialized) {
    // insert error on UART.
    return;
  }

  // Enable clock for TIM1 (or other timers as needed)
  // ENABLE_TIM1_CLOCK();
	
	// Reset TIM2 configuration
    TIM1->CR1 = 0;  // Enable auto-reload preload
    TIM1->CR1 |= TIM_CR1_CEN;  // Enable counter (CEN bit)


  // Store configuration
  PwmChannelConfig[0] = ConfigPtr[0];

  // Configure the timer for PWM
  TIM1->PSC =
      15; // Prescaler value (adjust based on clock and desired frequency)
  TIM1->ARR = ConfigPtr[0].defaultPeriod;     // Set auto-reload value
  TIM1->CCR1 = ConfigPtr[0].defaultDutyCycle; // Set initial duty cycle

  // Configure PWM Mode 1 for Channel 1
  TIM1->CCMR1 |= TIM_CCMR1_OC1M_PWM1; // Set PWM mode 1
  TIM1->CCMR1 |= (1 << 3);            // Enable output compare preload

  // Enable output and configure polarity
  if (ConfigPtr[0].polarity == PWM_HIGH) {
    TIM1->CCER |= TIM_CCER_CC1E; // Enable capture/compare output for Channel 1
  } else {
    TIM1->CCER &= ~TIM_CCER_CC1P; // Set low polarity
  }

  // Start the timer
  TIM1->CR1 |= TIM_CR1_CEN; // Enable counter

  PwmInitialized = TRUE;
}

// Function to deinitialize PWM
void Pwm_Deinit(void) {
  if (!PwmInitialized) {
    // Insert error on UART.
    return;
  }

  // Stop the timer
  TIM1->CR1 &= ~TIM_CR1_CEN; // Disable counter

  // Disable the PWM output
  TIM1->CCER &= ~TIM_CCER_CC1E; // Disable capture/compare output for Channel 1

  // Optionally, reset the configuration values
  TIM1->PSC = 0;
  TIM1->ARR = 0;
  TIM1->CCR1 = 0;

  // Disable clock for TIM1 (if needed)
  DISABLE_TIM1_CLOCK();

  PwmInitialized = FALSE; // Mark PWM as uninitialized
}

// Function to set the duty cycle for a PWM channel
void Pwm_SetDutyCycle(Pwm_ChannelType channel, uint16_t dutyCycle) {
  if (!PwmInitialized) {
    // Insert error on UART if PWM is not initialized
    return;
  }

  // Validate the channel (assuming only one channel for simplicity)
  if (channel != 0) {
    // Insert error on UART for invalid channel
    return;
  }

  // Validate the duty cycle
  if (dutyCycle > TIM1->ARR) {
    // Insert error on UART for duty cycle out of range
    return;
  }

  // Set the new duty cycle
  TIM1->CCR1 = dutyCycle; // Update the compare value for Channel 1
}

// Function to set PWM period and duty cycle
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period,
                          Pwm_DutyCycleType DutyCycle) {
  // Check if PWM has been initialized
  if (!PwmInitialized) {
    // Insert error handling (e.g., send error on UART)
    return;
  }

  // Validate the channel number
  if (ChannelNumber != 0) {
    // Insert error handling for invalid channel
    return;
  }

  // Update the auto-reload register for the new period
  TIM1->ARR = Period;

  // Update the capture/compare register for the new duty cycle
  TIM1->CCR1 = DutyCycle;

  // Optionally trigger an update event to apply changes immediately
  TIM1->EGR |= TIM_EGR_UG; // Generate an update event
}

// Function to get the output state of a PWM channel
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType channel) {
  if (!PwmInitialized) {
    // Insert error handling (e.g., send error on UART)
    return FALSE; // Or handle as appropriate
  }

  // Validate the channel (assuming only one channel for simplicity)
  if (channel != 0) {
    // Insert error handling for invalid channel
    return FALSE; // Or handle as appropriate
  }

  // Check if the output is enabled
  return (TIM1->CCER & TIM_CCER_CC1E) !=
         0; // Return TRUE if enabled, FALSE otherwise
}

void Pwm_SetOutputToIdle(Pwm_ChannelType channel) {
  if (!PwmInitialized) {
    // Log error (e.g., via UART) that PWM is not initialized
    return;
  }

  // Validate the channel number
  if (channel != 0) {
    // Log error (e.g., via UART) for invalid channel
    return;
  }

  // Disable PWM output for the specified channel
  TIM1->CCER &= ~TIM_CCER_CC1E; // Disable capture/compare output for Channel 1

  // Reset the duty cycle to idle (zero)
  TIM1->CCR1 = 0; // Set capture/compare register to zero

  // Optionally trigger an update event to apply changes
  TIM1->EGR |= TIM_EGR_UG; // Generate an update event
}
