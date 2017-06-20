/*
 * DO NOT EDIT! generated by embed_mruby_code.pl
 * Please refer to the respective source files for copyright information.
 */

/* lib/handler/mruby/embedded/core.rb */
#define H2O_MRUBY_CODE_CORE                                                                                                        \
    "$__TOP_SELF__ = self\n"                                                                                                       \
    "def _h2o_eval_conf(__h2o_conf)\n"                                                                                             \
    "  $__TOP_SELF__.eval(__h2o_conf[:code], nil, __h2o_conf[:file], __h2o_conf[:line])\n"                                         \
    "end\n"                                                                                                                        \
    "module Kernel\n"                                                                                                              \
    "  def _h2o_define_callback(name, id)\n"                                                                                       \
    "    Kernel.define_method(name) do |*args|\n"                                                                                  \
    "      ret = Fiber.yield([ id, _h2o_create_resumer(), args ])\n"                                                               \
    "      if ret.kind_of? Exception\n"                                                                                            \
    "        raise ret\n"                                                                                                          \
    "      end\n"                                                                                                                  \
    "      ret\n"                                                                                                                  \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  def _h2o_create_resumer()\n"                                                                                                \
    "    me = Fiber.current\n"                                                                                                     \
    "    Proc.new do |v|\n"                                                                                                        \
    "    me.resume(v)\n"                                                                                                           \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  def _h2o_proc_each_to_array()\n"                                                                                            \
    "    Proc.new do |o|\n"                                                                                                        \
    "      a = []\n"                                                                                                               \
    "      o.each do |x|\n"                                                                                                        \
    "        a << x\n"                                                                                                             \
    "      end\n"                                                                                                                  \
    "      a\n"                                                                                                                    \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  H2O_CALLBACK_ID_EXCEPTION_RAISED = -1\n"                                                                                    \
    "  H2O_CALLBACK_ID_CONFIGURING_APP = -2\n"                                                                                     \
    "  H2O_CALLBACK_ID_CONFIGURED_APP = -3\n"                                                                                      \
    "  def _h2o_prepare_app(conf)\n"                                                                                               \
    "    app = Proc.new do |req|\n"                                                                                                \
    "      [H2O_CALLBACK_ID_CONFIGURING_APP]\n"                                                                                    \
    "    end\n"                                                                                                                    \
    "    cached = nil\n"                                                                                                           \
    "    runner = Proc.new do |args|\n"                                                                                            \
    "      fiber = cached || Fiber.new do |req, generator|\n"                                                                      \
    "        self_fiber = Fiber.current\n"                                                                                         \
    "        while 1\n"                                                                                                            \
    "          begin\n"                                                                                                            \
    "            while 1\n"                                                                                                        \
    "              H2O.set_generator(self_fiber, generator)\n"                                                                     \
    "              resp = app.call(req)\n"                                                                                         \
    "              H2O.set_generator(self_fiber, nil)\n"                                                                           \
    "              cached = self_fiber\n"                                                                                          \
    "              (req, generator) = Fiber.yield(*resp, generator)\n"                                                             \
    "            end\n"                                                                                                            \
    "          rescue => e\n"                                                                                                      \
    "            H2O.set_generator(self_fiber, nil)\n"                                                                             \
    "            cached = self_fiber\n"                                                                                            \
    "            (req, generator) = Fiber.yield([H2O_CALLBACK_ID_EXCEPTION_RAISED, e, generator])\n"                               \
    "          end\n"                                                                                                              \
    "        end\n"                                                                                                                \
    "      end\n"                                                                                                                  \
    "      cached = nil\n"                                                                                                         \
    "      fiber.resume(*args)\n"                                                                                                  \
    "    end\n"                                                                                                                    \
    "    configurator = Proc.new do\n"                                                                                             \
    "      fiber = Fiber.new do\n"                                                                                                 \
    "        begin\n"                                                                                                              \
    "          H2O::ConfigurationContext.reset\n"                                                                                  \
    "          app = _h2o_eval_conf(conf)\n"                                                                                       \
    "          H2O::ConfigurationContext.instance.call_post_handler_generation_hooks(app)\n"                                       \
    "          [H2O_CALLBACK_ID_CONFIGURED_APP]\n"                                                                                 \
    "        rescue => e\n"                                                                                                        \
    "          app = Proc.new do |req|\n"                                                                                          \
    "            [500, {}, ['Internal Server Error']]\n"                                                                           \
    "          end\n"                                                                                                              \
    "          [H2O_CALLBACK_ID_CONFIGURED_APP, e]\n"                                                                              \
    "        end\n"                                                                                                                \
    "      end\n"                                                                                                                  \
    "      fiber.resume\n"                                                                                                         \
    "    end\n"                                                                                                                    \
    "    [runner, configurator]\n"                                                                                                 \
    "  end\n"                                                                                                                      \
    "end\n"                                                                                                                        \
    "module H2O\n"                                                                                                                 \
    "  class App\n"                                                                                                                \
    "    def call(env)\n"                                                                                                          \
    "      generator = H2O.get_generator(Fiber.current)\n"                                                                         \
    "      _h2o_invoke_app(env, generator, false)\n"                                                                               \
    "    end\n"                                                                                                                    \
    "    def reprocess(env)\n"                                                                                                     \
    "      generator = H2O.get_generator(Fiber.current)\n"                                                                         \
    "      _h2o_invoke_app(env, generator, true)\n"                                                                                \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  class << self\n"                                                                                                            \
    "    @@app = App.new\n"                                                                                                        \
    "    def app\n"                                                                                                                \
    "      @@app\n"                                                                                                                \
    "    end\n"                                                                                                                    \
    "    # mruby doesn't allow built-in object (i.e Fiber) to have instance variable\n"                                            \
    "    # so manage it with hash table here\n"                                                                                    \
    "    @@fiber_to_generator = {}\n"                                                                                              \
    "    def set_generator(fiber, generator)\n"                                                                                    \
    "        if generator.nil?\n"                                                                                                  \
    "          @@fiber_to_generator.delete(fiber.object_id)\n"                                                                     \
    "        else\n"                                                                                                               \
    "          @@fiber_to_generator[fiber.object_id] = generator\n"                                                                \
    "        end\n"                                                                                                                \
    "    end\n"                                                                                                                    \
    "    def get_generator(fiber)\n"                                                                                               \
    "        @@fiber_to_generator[fiber.object_id]\n"                                                                              \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  class OutputFilterStream\n"                                                                                                 \
    "    def initialize\n"                                                                                                         \
    "      @chunks = []\n"                                                                                                         \
    "      @finished = false\n"                                                                                                    \
    "    end\n"                                                                                                                    \
    "    def _push_chunks(chunks, finished)\n"                                                                                     \
    "      @chunks.concat(chunks)\n"                                                                                               \
    "      if finished\n"                                                                                                          \
    "        @finished = true\n"                                                                                                   \
    "      end\n"                                                                                                                  \
    "    end\n"                                                                                                                    \
    "    def each\n"                                                                                                               \
    "      loop do\n"                                                                                                              \
    "        while c = @chunks.shift\n"                                                                                            \
    "          yield c\n"                                                                                                          \
    "        end\n"                                                                                                                \
    "        if @finished\n"                                                                                                       \
    "          break\n"                                                                                                            \
    "        end\n"                                                                                                                \
    "        _h2o_output_filter_wait_chunk(self)\n"                                                                                \
    "      end\n"                                                                                                                  \
    "    end\n"                                                                                                                    \
    "    def join\n"                                                                                                               \
    "      s = \"\"\n"                                                                                                             \
    "      each do |c|\n"                                                                                                          \
    "        s << c\n"                                                                                                             \
    "      end\n"                                                                                                                  \
    "      s\n"                                                                                                                    \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "end\n"

/* lib/handler/mruby/embedded/http_request.rb */
#define H2O_MRUBY_CODE_HTTP_REQUEST                                                                                                \
    "module H2O\n"                                                                                                                 \
    "  class HttpRequest\n"                                                                                                        \
    "    def join\n"                                                                                                               \
    "      if !@resp\n"                                                                                                            \
    "        @resp = _h2o__http_join_response(self)\n"                                                                             \
    "      end\n"                                                                                                                  \
    "      @resp\n"                                                                                                                \
    "    end\n"                                                                                                                    \
    "    def _set_response(resp)\n"                                                                                                \
    "      @resp = resp\n"                                                                                                         \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "  class HttpInputStream\n"                                                                                                    \
    "    def each\n"                                                                                                               \
    "      while c = _h2o__http_fetch_chunk(self)\n"                                                                               \
    "        yield c\n"                                                                                                            \
    "      end\n"                                                                                                                  \
    "    end\n"                                                                                                                    \
    "    def join\n"                                                                                                               \
    "      s = \"\"\n"                                                                                                             \
    "      each do |c|\n"                                                                                                          \
    "        s << c\n"                                                                                                             \
    "      end\n"                                                                                                                  \
    "      s\n"                                                                                                                    \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "end\n"

/* lib/handler/mruby/embedded/chunked.rb */
#define H2O_MRUBY_CODE_CHUNKED                                                                                                     \
    "module Kernel\n"                                                                                                              \
    "  def _h2o_chunked_proc_each_to_fiber()\n"                                                                                    \
    "    Proc.new do |args|\n"                                                                                                     \
    "      src, generator = *args\n"                                                                                               \
    "      fiber = Fiber.new do\n"                                                                                                 \
    "        begin\n"                                                                                                              \
    "          src.each do |chunk|\n"                                                                                              \
    "            _h2o_send_chunk(chunk, generator)\n"                                                                              \
    "          end\n"                                                                                                              \
    "          _h2o_send_chunk_eos(generator)\n"                                                                                   \
    "        rescue => e\n"                                                                                                        \
    "          Fiber.yield([-1, e, generator])\n"                                                                                  \
    "        end\n"                                                                                                                \
    "      end\n"                                                                                                                  \
    "      fiber.resume\n"                                                                                                         \
    "    end\n"                                                                                                                    \
    "  end\n"                                                                                                                      \
    "end\n"
